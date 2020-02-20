/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Transformation implementation
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <math.h>

#include <transformation.h>

Matrix translation(double x, double y, double z)
{
   Matrix ret = Matrix4().identity();
   
   ret.set(0, 3, x);
   ret.set(1, 3, y);
   ret.set(2, 3, z);
   
   return ret;
}

Matrix scaling(double x, double y, double z)
{
   Matrix ret = Matrix4();
   
   ret.set(0, 0, x);
   ret.set(1, 1, y);
   ret.set(2, 2, z);
   ret.set(3, 3, 1);
   
   return ret;
}

Matrix rotationX(double angle)
{
   Matrix ret = Matrix4().identity();
   
   ret.set(1, 1, cos(angle));
   ret.set(1, 2, -sin(angle));
   ret.set(2, 1, sin(angle));
   ret.set(2, 2, cos(angle));
   
   return ret;
}

Matrix rotationY(double angle)
{
   Matrix ret = Matrix4().identity();
   
   ret.set(0, 0, cos(angle));
   ret.set(0, 2, sin(angle));
   ret.set(2, 0, -sin(angle));
   ret.set(2, 2, cos(angle));
   
   return ret;
}

Matrix rotationZ(double angle)
{
   Matrix ret = Matrix4().identity();
   
   ret.set(0, 0, cos(angle));
   ret.set(0, 1, -sin(angle));
   ret.set(1, 0, sin(angle));
   ret.set(1, 1, cos(angle));
   
   return ret;
}

Matrix shearing(double Xy, double Xz, double Yx, double Yz, double Zx, double Zy)
{
    Matrix ret = Matrix4().identity();

    ret.set(0, 1, Xy);
    ret.set(0, 2, Xz);
    ret.set(1, 0, Yx);
    ret.set(1, 2, Yz);
    ret.set(2, 0, Zx);
    ret.set(2, 1, Zy);

    return ret;
}

Matrix viewTransform(Tuple from, Tuple to, Tuple up)
{
    Tuple forward = (to - from).normalise();
    Tuple left = forward.cross(up.normalise());
    Tuple true_up = left.cross(forward);

    double orientationValues[] = {  left.x,     left.y,     left.z,    0,
                                    true_up.x,  true_up.y,  true_up.z, 0,
                                   -forward.x, -forward.y, -forward.z, 0,
                                    0,          0,          0,         1 };
    Matrix orientation = Matrix4(orientationValues);

    return orientation * translation(-from.x, -from.y, -from.z);
}