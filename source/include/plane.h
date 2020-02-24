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

class Plane : public Shape
{
private:
    Intersect localIntersect(Ray r);
    Tuple localNormalAt(Tuple point);

public:
    Plane() : Shape(SHAPE_PLANE) { };
    BoundingBox getBounds();
};

#endif //DORAYME_PLANE_H
