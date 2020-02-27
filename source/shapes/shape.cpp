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
    this->parent = nullptr;
    this->dropShadow = true;
    this->type = type;
    this->localTransformMatrix = Matrix4().identity();
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

Tuple Shape::normalAt(Tuple point)
{
    Tuple local_point = this->worldToObject(point);

    Tuple local_normal = this->localNormalAt(local_point);

    Tuple world_normal = this->normalToWorld(local_normal);

    return world_normal;
}

void Shape::updateTransform()
{
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
    this->localTransformMatrix = transform;
    this->updateTransform();
}

BoundingBox Shape::getBounds()
{
    BoundingBox ret;

    ret.min = this->objectToWorld(Point(-1, -1, -1));
    ret.max = this->objectToWorld(Point(1, 1, 1));
    return ret;
}

void Shape::dumpMe(FILE *fp)
{
    fprintf(fp, "\"Material\": {\n");
    this->material.dumpMe(fp);
    fprintf(fp, "},\n");
    fprintf(fp, "\"DropShadow\": %d,\n", this->dropShadow);
}