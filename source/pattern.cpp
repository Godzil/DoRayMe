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
#include <stdio.h>

Pattern::Pattern(Colour a, Colour b): a(a), b(b)
{
    this->transformMatrix = Matrix4().identity();
    this->inverseTransform = this->transformMatrix.inverse();
};

Colour Pattern::patternAtObject(Shape *object, Tuple worldPoint)
{
    Tuple objectPoint = object->worldToObject(worldPoint);
    Tuple patternPoint = this->inverseTransform * objectPoint;

    return this->patternAt(patternPoint);
}

void Pattern::setTransform(Matrix transform)
{
    this->transformMatrix = transform;
    this->inverseTransform = transform.inverse();
}

void Pattern::dumpMe(FILE *fp)
{
    fprintf(fp, "\"Colour A\": {\"red\": %f, \"green\": %f, \"blue\": %f},\n", this->a.x, this->a.y, this->a.z);
    fprintf(fp, "\"Colour B\": {\"red\": %f, \"green\": %f, \"blue\": %f},\n", this->b.x, this->b.y, this->b.z);
}