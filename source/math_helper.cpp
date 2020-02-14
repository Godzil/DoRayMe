/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Math helping functions
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */

#include <math.h>
#include <float.h>
#include <math_helper.h>

bool double_equal(double a, double b)
{
    return fabs(a - b) < DBL_EPSILON;
}
