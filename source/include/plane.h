/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Plane header
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#ifndef DORAYME_PLANE_H
#define DORAYME_PLANE_H

#include <renderstat.h>

class Plane : public Shape
{
protected:
    Intersect localIntersect(Ray r);
    Tuple localNormalAt(Tuple point, Intersection *hit = nullptr);

public:
    Plane() : Shape(Shape::PLANE) { stats.addPlane(); };
    BoundingBox getLocalBounds();
    bool haveFiniteBounds() { return false; };
};

#endif //DORAYME_PLANE_H
