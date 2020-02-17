/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Object header
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#ifndef DORAYME_OBJECT_H
#define DORAYME_OBJECT_H

class Object;

#include <ray.h>
#include <tuple.h>
#include <matrix.h>
#include <intersect.h>
#include <material.h>

/* Base class for all object that can be presented in the world */
class Object
{
public:
    Matrix transformMatrix;
    Matrix inverseTransform;
    Material material;

public:
    Object();

    virtual Intersect intersect(Ray r);
    virtual Tuple normalAt(Tuple point);

    void setTransform(Matrix transform);
    void setMaterial(Material material) { this->material = material; };
    Ray transform(Ray r) {  return Ray(this->transformMatrix * r.origin, this->transformMatrix * r.direction); };
    Ray invTransform(Ray r) {  return Ray(this->inverseTransform * r.origin, this->inverseTransform * r.direction); };
};

#endif //DORAYME_OBJECT_H
