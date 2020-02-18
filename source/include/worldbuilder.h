/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Worldbuilder header
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#ifndef DORAYME_WORLDBUILDER_H
#define DORAYME_WORLDBUILDER_H

#include <world.h>

/* Let's keep a single header for now, will see later */

class DefaultWorld : World
{
public:
    DefaultWorld();
};

/* Not implemented yet */
class Hw3File : World
{
public:
    Hw3File(const char *filename);
};

#endif //DORAYME_WORLDBUILDER_H
