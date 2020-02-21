/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Pattern implementation
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */

#include <pattern.h>
#include <shape.h>

Pattern::Pattern(Colour a, Colour b): a(a), b(b)
{
    this->transformMatrix = Matrix4().identity();
    this->inverseTransform = this->transformMatrix.inverse();
};

Colour Pattern::patternAtObject(Shape *object, Tuple worldPoint)
{
    Tuple objectPoint = object->inverseTransform * worldPoint;
    Tuple patternPoint = this->inverseTransform * objectPoint;

    return this->patternAt(patternPoint);
}

void Pattern::setTransform(Matrix transform)
{
    this->transformMatrix = transform;
    this->inverseTransform = transform.inverse();
}