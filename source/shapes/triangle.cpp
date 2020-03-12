/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Triangle implementation
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <ray.h>
#include <shape.h>
#include <triangle.h>
#include <math_helper.h>
#include <renderstat.h>

Triangle::Triangle(Point p1, Point p2, Point p3) : Shape(Shape::TRIANGLE), p1(p1), p2(p2), p3(p3)
{
    stats.addTriangle();

    this->e1 = p2 - p1;
    this->e2 = p3 - p1;
    this->normal = e2.cross(e1).normalise();
}

void Triangle::localIntersect(Ray r, Intersect &xs)
{
    Tuple dirCrossE2 = r.direction.cross(this->e2);
    double determinant = this->e1.dot(dirCrossE2);
    if (fabs(determinant) < getEpsilon())
    {
        return;
    }

    double f = 1.0 / determinant;
    Tuple p1ToOrigin = r.origin - this->p1;
    Tuple originCrossE1 = p1ToOrigin.cross(this->e1);
    double u = f * p1ToOrigin.dot(dirCrossE2);
    double v = f * r.direction.dot(originCrossE1);

    if ((u < 0) || (u > 1))
    {
        return;
    }

    if ((v < 0) || ((u + v) > 1))
    {
        return;
    }

    double t = f * this->e2.dot(originCrossE1);
    xs.add(Intersection(t, this, u, v));
}

Tuple Triangle::localNormalAt(Tuple point, Intersection *hit)
{
    return this->normal;
}

BoundingBox Triangle::getLocalBounds()
{
    BoundingBox ret;

    ret | p1;
    ret | p2;
    ret | p3;

    return ret;
}

void Triangle::dumpMe(FILE *fp)
{
    fprintf(fp, "\"Type\": \"Triangle\",\n");

    /* World points*/
    Tuple t = this->transformMatrix * this->p1;
    fprintf(fp, "\"p1\": { \"x\": %f, \"y\": %f, \"z\": %f}, \n",
            t.x, t.y, t.z);
    t = this->transformMatrix * this->p2;
    fprintf(fp, "\"p2\": { \"x\": %f, \"y\": %f, \"z\": %f}, \n",
            t.x, t.y, t.z);
    t = this->transformMatrix * this->p3;
    fprintf(fp, "\"p3\": { \"x\": %f, \"y\": %f, \"z\": %f}, \n",
            t.x, t.y, t.z);

    /* Local points */
    t = this->p1;
    fprintf(fp, "\"lp1\": { \"x\": %f, \"y\": %f, \"z\": %f}, \n",
            t.x, t.y, t.z);
    t = this->p2;
    fprintf(fp, "\"lp2\": { \"x\": %f, \"y\": %f, \"z\": %f}, \n",
            t.x, t.y, t.z);
    t = this->p3;
    fprintf(fp, "\"lp3\": { \"x\": %f, \"y\": %f, \"z\": %f}, \n",
            t.x, t.y, t.z);
    Shape::dumpMe(fp);
}