/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Light implementation
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <stdio.h>
#include <light.h>

void Light::dumpMe(FILE *fp)
{
    fprintf(fp, "\"Colour\": {\"red\": %f, \"green\": %f, \"blue\": %f},\n",
            this->intensity.x, this->intensity.y, this->intensity.z);
    fprintf(fp, "\"Position\": {\"x\": %f, \"y\": %f, \"z\":%f},\n",
            this->position.x, this->position.y, this->position.z);
    fprintf(fp, "\"Type\": \"PointLight\",\n");
}