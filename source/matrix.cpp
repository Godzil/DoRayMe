/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Matrix implementation
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */

#include <stdio.h>
#include <matrix.h>
#include <tuple.h>
#include <math_helper.h>

Matrix::Matrix(int width)
{
    int i;

    this->size = width;

    for(i = 0; i < width*width; i++)
    {
        this->data[i] = 0;
    }
};

Matrix::Matrix(double values[], int width)
{
    int x, y;

    this->size = width;

    for(y = 0; y < this->size; y++)
    {
        for (x = 0 ; x < this->size ; x++)
        {
            this->data[this->size * x + y] = values[this->size * x + y];
        }
    }
};

bool Matrix::operator==(const Matrix &b) const
{
    int i;
    if (this->size != b.size)
    {
        /* If they are not the same size don't even bother */
        return false;
    }

    for(i = 0; i < this->size*this->size; i++)
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
    if (this->size != b.size)
    {
        /* If they are not the same size don't even bother */
        return true;
    }

    for(i = 0; i < this->size*this->size; i++)
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
    Matrix ret = Matrix(this->size);

    if (this->size == b.size)
    {
        for (y = 0 ; y < this->size ; y++)
        {
            for (x = 0 ; x < this->size ; x++)
            {
                double v = 0;
                for (k = 0 ; k < this->size ; k++)
                {
                    v += this->get(x, k) * b.get(k, y);
                }
                ret.set(x, y, v);
            }
        }
    }
    return ret;
}

/* TODO: Check if we can optimise this function. It is called a lot */
Tuple Matrix::operator*(const Tuple &b) const
{
    return Tuple(b.x * this->get(0, 0) + b.y * this->get(0, 1) + b.z * this->get(0, 2) + b.w * this->get(0, 3),
                 b.x * this->get(1, 0) + b.y * this->get(1, 1) + b.z * this->get(1, 2) + b.w * this->get(1, 3),
                 b.x * this->get(2, 0) + b.y * this->get(2, 1) + b.z * this->get(2, 2) + b.w * this->get(2, 3),
                 b.x * this->get(3, 0) + b.y * this->get(3, 1) + b.z * this->get(3, 2) + b.w * this->get(3, 3));
}

Matrix Matrix::identity()
{
    int i;
    for(i = 0; i < this->size; i++)
    {
        this->set(i, i, 1);
    }
    return *this;
}

Matrix Matrix::transpose()
{
    int x, y;
    Matrix ret = Matrix(this->size);

    for (y = 0 ; y < this->size ; y++)
    {
        for (x = 0 ; x < this->size ; x++)
        {
            ret.set(y, x, this->get(x, y));
        }
    }
    return ret;
}

Matrix Matrix::submatrix(int row, int column)
{
    int i, j;
    int x = 0, y = 0;
    Matrix ret = Matrix(this->size - 1);

    for (i = 0 ; i < this->size ; i++)
    {
        if (i == row)
        {
            /* Skip that row */
            continue;
        }
        y = 0;
        for (j = 0 ; j < this->size ; j++)
        {
            if (j == column)
            {
                /* skip that column */
                continue;
            }
            ret.set(x, y, this->get(i, j));
            y++;
        }
        x++;
    }
    return ret;
}

double Matrix::determinant()
{
    double det = 0;
    if (this->size == 2)
    {
        det = this->data[0] * this->data[3] - this->data[1] * this->data[2];
    }
    else
    {
        int col;
        for(col = 0; col < this->size; col++)
        {
            det = det + this->get(0, col) * this->cofactor(0, col);
        }
    }
    return det;
}

Matrix Matrix::inverse()
{
    Matrix ret = Matrix(this->size);

    if (this->isInvertible())
    {
        int row, col;
        double c;
        for (row = 0; row < this->size; row++)
        {
            for (col = 0; col < this->size; col++)
            {
                c = this->cofactor(row, col);
                ret.set(col, row, c / this->determinant());
            }
        }
    }

    return ret;
}