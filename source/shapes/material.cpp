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
#include <shape.h>

Colour Material::lighting(Light light, Tuple point, Tuple eyeVector, Tuple normalVector, Shape *hitObject, bool inShadow)
{
    Colour pointColor = this->colour;

    if (this->pattern != nullptr)
    {
        pointColor = this->pattern->patternAtObject(hitObject, point);
    }

    Tuple lightVector = (light.position - point).normalise();
    Tuple reflectVector = Tuple(0, 0, 0, 0);

    Tuple effectiveColour = pointColor * light.intensity;
    Tuple ambientColour = Colour(0, 0, 0);
    Tuple emissiveColour = Colour(0, 0, 0);
    Tuple diffuseColour = Colour(0, 0, 0);
    Tuple specularColour = Colour(0, 0, 0);
    Tuple finalColour = Colour(0, 0, 0);

    double lightDotNormal, reflectDotEye;

    ambientColour = effectiveColour * this->ambient;

    emissiveColour = pointColor * this->emissive;

    if (!inShadow)
    {
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
    }
    finalColour = emissiveColour + ambientColour + diffuseColour + specularColour;

    return Colour(finalColour.x, finalColour.y, finalColour.z);
}