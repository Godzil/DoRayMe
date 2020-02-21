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
    this->type = type;
    this->transformMatrix = Matrix4().identity();
    this->inverseTransform = this->transformMatrix.inverse();
}

Intersect Shape::intersect(Ray r)
{
    return this->localIntersect(this->invTransform(r));
};

Tuple Shape::normalAt(Tuple point)
{
    Tuple local_point = this->inverseTransform * point;

    Tuple local_normal = this->localNormalAt(local_point);

    Tuple world_normal = this->inverseTransform.transpose() * local_normal;

    /* W may get wrong, so hack it. This is perfectly normal as we are using a 4x4 matrix instead of a 3x3 */
    world_normal.w = 0;

    return world_normal.normalise();
}

void Shape::setTransform(Matrix transform)
{
    this->transformMatrix = transform;
    this->inverseTransform = transform.inverse();
}
