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

#include <tuple.h>

/* Some **** linux distro seems to define "minor" as a macro
 * and wreak havoc.
 * Let's make sure we are clean here 
 */
#ifdef minor
#undef minor
#endif

#define FastGet4(_x, _y) (this->data[4 * (_x) + (_y)])

class Matrix
{
protected:
    /* 4x4 is the default */
    double data[4*4];
    int size;

public:
    Matrix(int size = 4);
    Matrix(double values[], int size);

    double get(int x, int y) const { return this->data[this->size * x + y]; };
    void set(int x, int y, double v) { this->data[this->size * x + y] = v; };

    Matrix identity();
    Matrix transpose();
    double determinant();
    Matrix submatrix(int row, int column);
    Matrix inverse();
    double minor(int row, int column) { return this->submatrix(row, column).determinant(); }
    double cofactor(int row, int column) { return (((column+row)&1)?-1:1) * this->minor(row, column); }
    bool operator==(const Matrix &b) const;
    bool operator!=(const Matrix &b) const;

    bool isInvertible() { return this->determinant() != 0; }

    Matrix operator*(const Matrix &b) const;
    Tuple operator*(const Tuple &b) const {
        return Tuple(b.x * FastGet4(0, 0) + b.y * FastGet4(0, 1) + b.z * FastGet4(0, 2) + b.w * FastGet4(0, 3),
                     b.x * FastGet4(1, 0) + b.y * FastGet4(1, 1) + b.z * FastGet4(1, 2) + b.w * FastGet4(1, 3),
                     b.x * FastGet4(2, 0) + b.y * FastGet4(2, 1) + b.z * FastGet4(2, 2) + b.w * FastGet4(2, 3),
                     b.x * FastGet4(3, 0) + b.y * FastGet4(3, 1) + b.z * FastGet4(3, 2) + b.w * FastGet4(3, 3));
    }
};

class Matrix4: public Matrix
{
public:
    Matrix4() : Matrix(4) { };
    Matrix4(double values[]) : Matrix(values, 4) { };
};

class Matrix3 : public Matrix
{
public:
    Matrix3() : Matrix(3) { };
    Matrix3(double values[]) : Matrix(values, 3) { };
};

class Matrix2 : public Matrix
{
private:
    using Matrix::data;
public:
    Matrix2() : Matrix(2) { };
    Matrix2(double values[]) : Matrix(values, 2) { };
};

#endif /* DORAYME_MATRIX_H */
