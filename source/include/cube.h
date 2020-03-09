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
#include <renderstat.h>
#include <stdio.h>

class Cube : public Shape {
protected:
    void checkAxis(double axeOrigin, double axeDirection, double *axeMin, double *axeMax);

    Intersect localIntersect(Ray r);

    Tuple localNormalAt(Tuple point, Intersection *hit = nullptr);

public:
    Cube() : Shape(Shape::CUBE) { stats.addCube(); };

    void dumpMe(FILE *fp);
};

#endif /* DORAYME_CUBE_H */
