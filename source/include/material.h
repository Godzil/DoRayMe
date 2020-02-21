/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Material header
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#ifndef DORAYME_MATERIAL_H
#define DORAYME_MATERIAL_H

#include <tuple.h>
#include <colour.h>
#include <pattern.h>
#include <light.h>

class Shape;

class Material
{
public:
    Colour colour;
    double ambient;
    double diffuse;
    double specular;
    double shininess;
    double reflective;

    Pattern *pattern;

public:
    Material() : colour(Colour(1, 1, 1)), ambient(0.1), diffuse(0.9), specular(0.9), shininess(200), reflective(0.0), pattern(nullptr) {};

    Colour lighting(Light light, Tuple point, Tuple eyeVector, Tuple normalVector, Shape *hitObject, bool inShadow = false);

    bool operator==(const Material &b) const { return double_equal(this->ambient,   b.ambient) &&
                                                      double_equal(this->diffuse,   b.diffuse) &&
                                                      double_equal(this->specular,  b.specular) &&
                                                      double_equal(this->shininess, b.shininess) &&
                                                      (this->colour == b.colour); };
};

#endif /* DORAYME_MATERIAL_H */
