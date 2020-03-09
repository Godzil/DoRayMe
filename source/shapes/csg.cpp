/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Constructive Solid Geometry (CSG) implementation
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <tuple.h>
#include <ray.h>
#include <shape.h>
#include <csg.h>
#include <math_helper.h>


CSG::CSG(OperationType operation, Shape *left, Shape *right) : Shape(SHAPE_CSG), operation(operation), left(left), right(right)
{
    stats.addCsg();

    this->left->parent = this;
    this->right->parent = this;

    this->bounds | this->left->getBounds();
    this->bounds | this->right->getBounds();
}

Intersect CSG::localIntersect(Ray r)
{
    int i;
    Intersect leftxs = this->left->intersect(r);
    Intersect rightxs = this->right->intersect(r);

    for(i = 0; i < rightxs.count(); i++)
    {
        leftxs.add(rightxs[i]);
    }

    Intersect ret = this->filterIntersections(leftxs);

    return ret;
}

Intersect CSG::intersect(Ray r)
{
    return localIntersect(r);
}

Tuple CSG::localNormalAt(Tuple point, Intersection *hit)
{
    return Vector(1, 0, 0);
}

BoundingBox CSG::getLocalBounds()
{
    return this->bounds;
}

BoundingBox CSG::getBounds()
{
    if (this->bounds.isEmpty()) { this->updateBoundingBox(); }
    return this->bounds;
}

void CSG::updateBoundingBox()
{
    this->bounds.reset();

    this->bounds | this->left->getBounds();
    this->bounds | this->right->getBounds();
}

void CSG::updateTransform()
{
    Shape::updateTransform();

    this->left->updateTransform();
    this->right->updateTransform();

    /* Once the full stack being notified of the changes, let's update the
     * bounding box
     */
    this->updateBoundingBox();
}

bool CSG::includes(Shape *b)
{
    if (this->left->includes(b)) { return true; }
    if (this->right->includes(b)) { return true; }
    if (this == b) { return true; }
    return false;
}

bool CSG::intersectionAllowed(bool leftHit, bool inLeft, bool inRight)
{
    switch(this->operation)
    {
    case CSG::UNION:        return (leftHit && !inRight) || (!leftHit && !inLeft);
    case CSG::INTERSECTION: return (!leftHit && inLeft) || (leftHit && inRight);
    case CSG::DIFFERENCE:   return (leftHit && !inRight) || (!leftHit && inLeft);
    }
    return false;
}

void CSG::filterIntersections(Intersect &xs, Intersect &ret)
{
    bool inl = false;
    bool inr = false;

    int i;

    for(i = 0; i < xs.count(); i++)
    {
        bool lhit = this->left->includes(xs[i].object);

        if (this->intersectionAllowed(lhit, inl, inr))
        {
            ret.add(xs[i]);
        }

        if (lhit)
        {
            inl = !inl;
        }
        else
        {
            inr = !inr;
        }
    }
}

void CSG::dumpMe(FILE *fp)
{

}
