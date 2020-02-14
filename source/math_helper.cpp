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

static double current_precision = FLT_EPSILON;

void set_equal_precision(double v)
{
    current_precision = v;
}

bool double_equal(double a, double b)
{
    return fabs(a - b) < current_precision;
}
