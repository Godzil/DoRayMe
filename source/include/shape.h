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

#include <stdio.h>
#include <ray.h>
#include <tuple.h>
#include <matrix.h>
#include <intersect.h>
#include <material.h>
#include <boundingbox.h>

/* Base class for all object that can be presented in the world */
class Shape
{
public:
    enum ShapeType
    {
        NONE,
        SPHERE,
        PLANE,
        CUBE,
        CYLINDER,
        CONE,
        GROUP,
        TRIANGLE,
        OBJFILE,
        SMOOTHTRIANGLE,
        CSG,
    };

protected:
    ShapeType type;
    Matrix localTransformMatrix;
    bool locked;
    uint64_t objectId;

protected:
    virtual void localIntersect(Ray r, Intersect &xs) = 0;
    virtual Tuple localNormalAt(Tuple point, Intersection *hit) = 0;

    static uint64_t newObjectId();

public:
    Matrix transformMatrix;
    Matrix inverseTransform;
    Matrix transposedInverseTransform;

    Material material;
    bool dropShadow;
    Shape *parent;
    bool materialSet;

public:
    Shape(ShapeType = Shape::NONE);

    ShapeType getType() { return this->type; };

    virtual void intersect(Ray &r, Intersect &xs) { this->localIntersect(this->invTransform(r), xs); };
    Tuple normalAt(Tuple point, Intersection *hit = nullptr);

    uint64_t getObjectId() { return this->objectId; };
    void setObjectId(uint64_t oid) { this->objectId = oid; };

    /* Bounding box points are always world value */
    virtual BoundingBox getLocalBounds();
    virtual BoundingBox getBounds();
    virtual bool haveFiniteBounds() { return true; };

    virtual void updateTransform();

    virtual bool includes(Shape *b) { return this == b; };

    virtual void dumpMe(FILE *fp);

    /* When an object is locked, the matrix transformation and bounding box can't be updated. This is
     * usefull to move object between group without changing the real hierarchy between them.
     * It will also not change the parent member.
     * This is supposed to be used only before a render is going to start so we can optimise the
     * way the object are stored to prefer lots of un-needed intersections.
     */
    virtual void lock() { this->locked = true; };

    Tuple worldToObject(Tuple point) { return this->inverseTransform * point; };
    Tuple objectToWorld(Tuple point) { return this->transformMatrix * point; };
    Tuple normalToWorld(Tuple normalVector);

    void setParent(Shape *parent) { if (!this->locked) { this->parent = parent; };};

    void setTransform(Matrix transform);
    void setMaterial(Material material) { this->material = material; this->materialSet = true; };
    Material *getMaterial();
    Ray transform(Ray &r) { return Ray(this->transformMatrix * r.origin, this->transformMatrix * r.direction); };
    Ray invTransform(Ray &r) { return Ray(this->inverseTransform * r.origin, this->inverseTransform * r.direction); };

    bool operator==(const Shape &b) const { return this->material == b.material &&
                                                   this->type == b.type &&
                                                   this->transformMatrix == b.transformMatrix; };

};

#endif /* DORAYME_SHAPE_H */
