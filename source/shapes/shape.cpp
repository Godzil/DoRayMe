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
    return Intersect();
};

Tuple Shape::normalAt(Tuple point)
{
    return Vector(0, 0, 0);
}

void Shape::setTransform(Matrix transform)
{
    this->transformMatrix = transform;
    this->inverseTransform = transform.inverse();
}
