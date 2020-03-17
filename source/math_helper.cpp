/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Math helping functions
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */

#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <math_helper.h>

static double current_precision = FLT_EPSILON;

void set_equal_precision(double v)
{
    current_precision = v;
}

double getEpsilon()
{
    return current_precision;
}

bool double_equal(double a, double b)
{
    if (isinf(a) && isinf(b))
        return true;

    return fabs(a - b) < current_precision;
}

double deg_to_rad(double deg)
{
   return deg * M_PI / 180.;
}

double min3(double a, double b, double c)
{
    if (a <= b)
    {
        if (c < a) return c;
        return a;
    }
    if (b <= a)
    {
        if (c < b) return c;
    }
    return b;
}

double max3(double a, double b, double c)
{
    if (a >= b)
    {
        if (c > a) return c;
        return a;
    }
    if (b >= a)
    {
        if (c > b) return c;
    }
    return b;
}

double frand()
{
    return rand() / ((double) RAND_MAX);
}

double frandclip(double min, double max)
{
    return (frand() * (max - min)) + min;
}