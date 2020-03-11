/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Object implementation
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */

#include <ray.h>
#include <shape.h>
#include <matrix.h>
#include <tuple.h>
#include <intersect.h>

Shape::Shape(ShapeType type)
{
    this->locked = false;
    this->parent = nullptr;
    this->dropShadow = true;
    this->type = type;
    this->localTransformMatrix = Matrix4().identity();
    this->materialSet = false;

    this->updateTransform();
}

Intersect Shape::intersect(Ray r)
{
    return this->localIntersect(this->invTransform(r));
};

Tuple Shape::normalToWorld(Tuple normalVector)
{
    Tuple world_normal = this->transposedInverseTransform * normalVector;

    /* W may get wrong, so hack it. This is perfectly normal as we are using a 4x4 matrix instead of a 3x3 */
    world_normal.w = 0;

    return world_normal.normalise();
};

Tuple Shape::normalAt(Tuple point, Intersection *hit)
{
    Tuple local_point = this->worldToObject(point);

    Tuple local_normal = this->localNormalAt(local_point, hit);

    Tuple world_normal = this->normalToWorld(local_normal);

    return world_normal;
}

void Shape::updateTransform()
{
    if (this->locked) return;

    this->transformMatrix = this->localTransformMatrix;
    if (this->parent != nullptr)
    {
        this->transformMatrix = this->parent->transformMatrix * this->transformMatrix;
    }

    this->inverseTransform = this->transformMatrix.inverse();
    this->transposedInverseTransform = this->inverseTransform.transpose();
}

void Shape::setTransform(Matrix transform)
{
    if (this->locked) return;

    this->localTransformMatrix = transform;
    this->updateTransform();
}

BoundingBox Shape::getLocalBounds()
{
    return BoundingBox(Point(-1, -1, -1), Point(1,1,1));
}

BoundingBox Shape::getBounds()
{
    BoundingBox ret;
    BoundingBox me = this->getLocalBounds();

    ret | this->objectToWorld(Point(me.min.x, me.min.y, me.min.z));
    ret | this->objectToWorld(Point(me.min.x, me.min.y, me.max.z));
    ret | this->objectToWorld(Point(me.min.x, me.max.y, me.min.z));
    ret | this->objectToWorld(Point(me.max.x, me.min.y, me.min.z));
    ret | this->objectToWorld(Point(me.max.x, me.max.y, me.min.z));
    ret | this->objectToWorld(Point(me.max.x, me.min.y, me.max.z));
    ret | this->objectToWorld(Point(me.min.x, me.max.y, me.max.z));
    ret | this->objectToWorld(Point(me.max.x, me.max.y, me.max.z));

    return ret;
}

void Shape::dumpMe(FILE *fp)
{
    if (this->materialSet)
    {
        fprintf(fp, "\"Material\": {\n");
        this->material.dumpMe(fp);
        fprintf(fp, "},\n");
    }
    fprintf(fp, "\"DropShadow\": %d,\n", this->dropShadow);
    fprintf(fp, "\"Locked\": %d,\n", this->locked);
    fprintf(fp, "\"MaterialSet\": %d,\n", this->materialSet);
    if (this->haveFiniteBounds())
    {
        fprintf(fp, "\"BoundingBox\": {\n");
        this->getBounds().dumpMe(fp);
        fprintf(fp, "},\n");
    }
    fprintf(fp, "\"id\": %p,\n", this);
    if (this->parent)
    {
        fprintf(fp, "\"parentId\": %p,\n", this->parent);
    }
}