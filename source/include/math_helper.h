/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Math helping function header
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */

#ifndef DORAYME_MATH_HELPER_H
#define DORAYME_MATH_HELPER_H

#include <math.h>

void set_equal_precision(double v);
double getEpsilon();
bool double_equal(double a, double b);

double deg_to_rad(double deg);

double min3(double a, double b, double c);
double max3(double a, double b, double c);

double frand();

#endif /* DORAYME_MATH_HELPER_H */
