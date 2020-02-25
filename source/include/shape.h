/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Object header
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#ifndef DORAYME_SHAPE_H
#define DORAYME_SHAPE_H

class Shape;

#include <ray.h>
#include <tuple.h>
#include <matrix.h>
#include <intersect.h>
#include <material.h>
#include <boundingbox.h>

enum ShapeType
{
    SHAPE_NONE,
    SHAPE_SPHERE,
    SHAPE_PLANE,
    SHAPE_CUBE,
    SHAPE_CYLINDER,
    SHAPE_CONE,
    SHAPE_GROUP,

};

/* Base class for all object that can be presented in the world */
class Shape
{
private:
    ShapeType type;
    Matrix localTransformMatrix;
protected:
    virtual Intersect localIntersect(Ray r) = 0;
    virtual Tuple localNormalAt(Tuple point) = 0;

public:
    Matrix transformMatrix;
    Matrix inverseTransform;
    Matrix transposedInverseTransform;

    Material material;
    bool dropShadow;
    Shape *parent;

public:
    Shape(ShapeType = SHAPE_NONE);

    virtual Intersect intersect(Ray r);
    virtual Intersect intersectOOB(Ray r) { return this->intersect(r); };
    Tuple normalAt(Tuple point);

    /* Bounding box points are always world value */
    virtual BoundingBox getBounds();
    virtual bool haveFiniteBounds() { return true; };

    void updateTransform();
    Tuple worldToObject(Tuple point) { return this->inverseTransform * point; };
    Tuple objectToWorld(Tuple point) { return this->transformMatrix * point; };
    Tuple normalToWorld(Tuple normalVector);

    void setTransform(Matrix transform);
    void setMaterial(Material material) { this->material = material; };
    Ray transform(Ray r) {  return Ray(this->transformMatrix * r.origin, this->transformMatrix * r.direction); };
    Ray invTransform(Ray r) {  return Ray(this->inverseTransform * r.origin, this->inverseTransform * r.direction); };

    bool operator==(const Shape &b) const { return this->material == b.material &&
                                                   this->type == b.type &&
                                                   this->transformMatrix == b.transformMatrix; };

};

#endif /* DORAYME_SHAPE_H */
