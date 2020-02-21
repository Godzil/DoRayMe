/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Test shape header
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#ifndef DORAYME_TESTSHAPE_H
#define DORAYME_TESTSHAPE_H

#include <shape.h>
#include <ray.h>
#include <tuple.h>

class TestShape : public Shape
{
private:
    Intersect localIntersect(Ray r);
    Tuple localNormalAt(Tuple point);

public:
    Ray localRay;

    TestShape();
};

#endif //DORAYME_TESTSHAPE_H
