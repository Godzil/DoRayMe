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
private:
    Intersect localIntersect(Ray r);
    Tuple localNormalAt(Tuple point);

public:
    Plane() : Shape(SHAPE_PLANE) { stats.addPlane(); };
    BoundingBox getLocalBounds();
    bool haveFiniteBounds() { return false; };
};

#endif //DORAYME_PLANE_H
