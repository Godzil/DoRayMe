/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Transformation header
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#ifndef DORAYME_TRANSFORMATION_H
#define DORAYME_TRANSFORMATION_H

#include <matrix.h>

Matrix translation(double x, double y, double z);

Matrix scaling(double x, double y, double z);

Matrix rotation_x(double angle);
Matrix rotation_y(double angle);
Matrix rotation_z(double angle);

Matrix shearing(double Xy, double Xx, double Yx, double Yz, double Zx, double Zy);

#endif /* DORAYME_TRANSFORMATION_H */