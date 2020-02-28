/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Bounding box header
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#ifndef DORAYME_BOUNDINGBOX_H
#define DORAYME_BOUNDINGBOX_H

#include <renderstat.h>
#include <stdio.h>

struct BoundingBox
{
private:
    bool isReset;

public:
    Tuple min;
    Tuple max;

    BoundingBox() : min(INFINITY, INFINITY, INFINITY, 1.0), max(-INFINITY, -INFINITY, -INFINITY, 1.0), isReset(true) { };
    BoundingBox(Tuple min, Tuple max) : min(min), max(max), isReset(false) { };

    void operator|(const BoundingBox &b) {
        isReset = false;

        if (this->min.x > b.min.x) { this->min.x = b.min.x; }
        if (this->min.y > b.min.y) { this->min.y = b.min.y; }
        if (this->min.z > b.min.z) { this->min.z = b.min.z; }

        if (this->max.x < b.max.x) { this->max.x = b.max.x; }
        if (this->max.y < b.max.y) { this->max.y = b.max.y; }
        if (this->max.z < b.max.z) { this->max.z = b.max.z; }
    }

    void operator|(const Tuple &b) {
        isReset = false;

        if (this->min.x > b.x) { this->min.x = b.x; }
        if (this->min.y > b.y) { this->min.y = b.y; }
        if (this->min.z > b.z) { this->min.z = b.z; }

        if (this->max.x < b.x) { this->max.x = b.x; }
        if (this->max.y < b.y) { this->max.y = b.y; }
        if (this->max.z < b.z) { this->max.z = b.z; }
    }

    bool haveFiniteBounds() { return this->min.isRepresentable() && this->max.isRepresentable(); };

    bool fitsIn(const BoundingBox &other) {
        bool fits = true;

        if (this->min.x > other.min.x) { fits = false; }
        if (this->min.y > other.min.y) { fits = false; }
        if (this->min.z > other.min.z) { fits = false; }

        if (this->max.x < other.max.x) { fits = false; }
        if (this->max.y < other.max.y) { fits = false; }
        if (this->max.z < other.max.z) { fits = false; }

        return fits;
    }

    void checkAxis(double axeOrigin, double axeDirection, double xMin, double xMax, double *axeMin, double *axeMax)
    {
        double tMinNumerator = (xMin - axeOrigin);
        double tMaxNumerator = (xMax - axeOrigin);

        if (fabs(axeDirection) >= getEpsilon())
        {
            *axeMin = tMinNumerator / axeDirection;
            *axeMax = tMaxNumerator / axeDirection;
        }
        else
        {
            *axeMin = tMinNumerator * INFINITY;
            *axeMax = tMaxNumerator * INFINITY;
        }

        if (*axeMin > *axeMax)
        {
            double swap = *axeMax;
            *axeMax = *axeMin;
            *axeMin = swap;
        }
    }

    void reset()
    {
        this->isReset = true;
        min.x = min.y = min.z = INFINITY;
        max.x = max.y = max.z = -INFINITY;
    }

    bool isEmpty() { return this->isReset; };

    bool intesectMe(Ray r) {

        double xtMin, xtMax, ytMin, ytMax, ztMin, ztMax;
        double tMin, tMax;

        this->checkAxis(r.origin.x, r.direction.x, this->min.x, this->max.x, &xtMin, &xtMax);
        this->checkAxis(r.origin.y, r.direction.y, this->min.y, this->max.y, &ytMin, &ytMax);
        this->checkAxis(r.origin.z, r.direction.z, this->min.z, this->max.z, &ztMin, &ztMax);

        tMin = max3(xtMin, ytMin, ztMin);
        tMax = min3(xtMax, ytMax, ztMax);

        if (tMin <= tMax)
        {
            return true;
        }

        stats.addDiscardedIntersect();

        return false;
    }

    void dumpMe(FILE *fp)
    {
        Tuple t = this->min;
        fprintf(fp, "\"min\": { \"x\": %f, \"y\": %f, \"z\": %f}, \n",
                t.x, t.y, t.z);
        t = this->max;
        fprintf(fp, "\"max\": { \"x\": %f, \"y\": %f, \"z\": %f}, \n",
                t.x, t.y, t.z);
    }

};

#endif /* DORAYME_BOUNDINGBOX_H */
