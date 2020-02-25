/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Cube header
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#ifndef DORAYME_CUBE_H
#define DORAYME_CUBE_H

#include <shape.h>
#include <ray.h>
#include <intersect.h>

class Cube : public Shape {
private:
    void checkAxis(double axeOrigin, double axeDirection, double *axeMin, double *axeMax);

    Intersect localIntersect(Ray r);

    Tuple localNormalAt(Tuple point);

public:
    Cube() : Shape(SHAPE_CUBE) {};
};

#endif /* DORAYME_CUBE_H */
