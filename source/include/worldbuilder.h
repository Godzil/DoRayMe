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
#include <camera.h>

/* Let's keep a single header for now, will see later */

class DefaultWorld : public World
{
public:
    DefaultWorld();
};

/* Not implemented yet */
class Hw3File : public World
{
private:
    Matrix transformStack[50];
    uint32_t transStackCount;

public:
    double currentAmbient;
    double currentShininess;
    double currentSpecular;
    double currentDiffuse;
    double currentEmission;
    double currentReflective;
    double currentTransparency;
    double currentRefIndex;

    Colour currentColour;
    Matrix cam;
    double camFoV;

public:
    Matrix getTransformMatrix();
    void popTransformMatrix();
    void pushTransformMatrix();
    void applyTransformMatrix(Matrix t);

    Hw3File(const char *filename);
};

#endif /* DORAYME_WORLDBUILDER_H */
