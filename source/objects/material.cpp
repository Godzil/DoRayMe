/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Material implementation
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <tuple.h>
#include <material.h>
#include <colour.h>

Colour Material::lighting(Light light, Tuple point, Tuple eyeVector, Tuple normalVector)
{
    Tuple lightVector = (light.position - point).normalise();
    Tuple reflectVector = Tuple(0, 0, 0, 0);

    Tuple effectiveColour = this->colour * light.intensity;
    Tuple ambientColour = Colour(0, 0, 0);
    Tuple diffuseColour = Colour(0, 0, 0);
    Tuple specularColour = Colour(0, 0, 0);
    Tuple finalColour = Colour(0, 0, 0);

    double lightDotNormal, reflectDotEye;

    ambientColour = effectiveColour * this->ambient;

    lightDotNormal = lightVector.dot(normalVector);

    if (lightDotNormal < 0)
    {
        diffuseColour = Colour(0, 0, 0);
        specularColour = Colour(0, 0, 0);
    }
    else
    {
        diffuseColour = effectiveColour * this->diffuse * lightDotNormal;
        reflectVector = -lightVector.reflect(normalVector);

        reflectDotEye = reflectVector.dot(eyeVector);

        if (reflectDotEye < 0)
        {
            specularColour = Colour(0, 0, 0);
        }
        else
        {
            double factor = pow(reflectDotEye, this->shininess);
            specularColour = light.intensity * this->specular * factor;
        }
    }

    finalColour = ambientColour + diffuseColour + specularColour;

    return Colour(finalColour.x, finalColour.y, finalColour.z);
}