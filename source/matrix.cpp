/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Matrix implementation
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */

#include <matrix.h>
#include <tuples.h>
#include <math_helper.h>

bool Matrix::operator==(const Matrix &b) const
{
    int i;
    if (this->width != b.width)
    {
        /* If they are not the same size don't even bother */
        return false;
    }

    for(i = 0; i < this->width*this->width; i++)
    {
        if (!double_equal(this->data[i], b.data[i]))
        {
            return false;
        }
    }

    return true;
}

bool Matrix::operator!=(const Matrix &b) const
{
    int i;
    if (this->width != b.width)
    {
        /* If they are not the same size don't even bother */
        return true;
    }

    for(i = 0; i < this->width*this->width; i++)
    {
        if (!double_equal(this->data[i], b.data[i]))
        {
            return true;
        }
    }
    return false;
}

Matrix Matrix::operator*(const Matrix &b) const
{
    int x, y, k;
    Matrix ret = Matrix(this->width);

    if (this->width == b.width)
    {
        for (y = 0 ; y < this->width ; y++)
        {
            for (x = 0 ; x < this->width ; x++)
            {
                double v = 0;
                for (k = 0 ; k < this->width ; k++)
                {
                    v += this->get(x, k) * b.get(k, y);
                }
                ret.set(x, y, v);
            }
        }
    }
    return ret;
}

Tuple Matrix::operator*(const Tuple &b) const
{
    return Tuple(b.x * this->get(0, 0) + b.y * this->get(0, 1) + b.z * this->get(0, 2) + b.w * this->get(0, 3),
                 b.x * this->get(1, 0) + b.y * this->get(1, 1) + b.z * this->get(1, 2) + b.w * this->get(1, 3),
                 b.x * this->get(2, 0) + b.y * this->get(2, 1) + b.z * this->get(2, 2) + b.w * this->get(2, 3),
                 b.x * this->get(3, 0) + b.y * this->get(3, 1) + b.z * this->get(3, 2) + b.w * this->get(3, 3));
}