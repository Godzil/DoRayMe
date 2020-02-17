/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Object implementation
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */

#include <ray.h>
#include <object.h>
#include <matrix.h>
#include <tuple.h>
#include <intersect.h>

Object::Object()
{
    this->transformMatrix = Matrix4().identity();
    this->inverseTransform = this->transformMatrix.inverse();
}

Intersect Object::intersect(Ray r)
{
    return Intersect();
};

void Object::setTransform(Matrix transform)
{
    this->transformMatrix = transform;
    this->inverseTransform = transform.inverse();
}
