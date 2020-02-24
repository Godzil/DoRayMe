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

struct BoundingBox
{
    Tuple min;
    Tuple max;

    BoundingBox() : min(-0, -0, -0), max(0, 0, 0) { };
    BoundingBox(Tuple min, Tuple max) : min(min), max(max) { };
};

#endif //DORAYME_BOUNDINGBOX_H
