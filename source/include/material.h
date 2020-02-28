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
#include <stdio.h>

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
    double transparency;
    double emissive;
    double refractiveIndex;

    Pattern *pattern;

public:
    Material() : colour(Colour(1, 1, 1)), ambient(0.1), diffuse(0.9), specular(0.9), shininess(200),
           reflective(0.0), transparency(0.0), emissive(0), refractiveIndex(1.0), pattern(nullptr) {};

    Colour lighting(Light light, Tuple point, Tuple eyeVector, Tuple normalVector, Shape *hitObject,
            double lightIntensity = 1.0);

    bool operator==(const Material &b) const { return double_equal(this->ambient,   b.ambient) &&
                                                      double_equal(this->diffuse,   b.diffuse) &&
                                                      double_equal(this->specular,  b.specular) &&
                                                      double_equal(this->shininess, b.shininess) &&
                                                      double_equal(this->reflective, b.reflective) &&
                                                      double_equal(this->transparency, b.transparency) &&
                                                      double_equal(this->emissive, b.emissive) &&
                                                      double_equal(this->refractiveIndex, b.refractiveIndex) &&
                                                      (this->colour == b.colour); };
    bool operator!=(const Material &b) const { return !(*this == b); };

    void dumpMe(FILE *fp);
};


#endif /* DORAYME_MATERIAL_H */
