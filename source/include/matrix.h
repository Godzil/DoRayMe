/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Matrix header
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#ifndef DORAYME_MATRIX_H
#define DORAYME_MATRIX_H

#include <tuples.h>

class Matrix
{
private:
    /* 4x4 is the default */
    double data[4*4];
    int width;

public:
    Matrix(int width) : width(width)
    {
        int i;
        for(i = 0; i < width*width; i++)
        {
            this->data[i] = 0;
        }
    };
    Matrix(double values[], int width)
    {
        int x, y;

        this->width = width;

        for(y = 0; y < this->width; y++)
        {
            for (x = 0 ; x < this->width ; x++)
            {
                this->data[this->width * x + y] = values[this->width * x + y];
            }
        }
    };
    double get(int x, int y) const { return this->data[this->width * x + y]; };
    void set(int x, int y, double v) { this->data[this->width * x + y] = v; };

    Matrix identity()
    {
        int i;
        for(i = 0; i < this->width; i++)
        {
            this->set(i, i, 1);
        }
        return *this;
    }

    Matrix transpose()
    {
        int x, y;
        Matrix ret = Matrix(this->width);
        for(y = 0; y < this->width; y++)
        {
            for (x = 0 ; x < this->width ; x++)
            {
                ret.set(y, x, this->get(x, y));
            }
        }
        return ret;
    }

    bool operator==(const Matrix &b) const;
    bool operator!=(const Matrix &b) const;

    Matrix operator*(const Matrix &b) const;
    Tuple operator*(const Tuple &b) const;
};

class Matrix4: public Matrix
{
public:
    Matrix4() : Matrix(4) { };
    Matrix4(double values[]) : Matrix(values, 4) { };
};


class Matrix2 : public Matrix
{
public:
    Matrix2() : Matrix(2) { };
    Matrix2(double values[]) : Matrix(values, 2) { };
};

class Matrix3 : public Matrix
{
public:
    Matrix3() : Matrix(3) { };
    Matrix3(double values[]) : Matrix(values, 3) { };
};

#endif /* DORAYME_MATRIX_H */
