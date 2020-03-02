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
#include <world.h>

void Light::dumpMe(FILE *fp)
{
    fprintf(fp, "\"Colour\": {\"red\": %f, \"green\": %f, \"blue\": %f},\n",
            this->intensity.x, this->intensity.y, this->intensity.z);
    fprintf(fp, "\"Position\": {\"x\": %f, \"y\": %f, \"z\":%f},\n",
            this->position.x, this->position.y, this->position.z);
    fprintf(fp, "\"Type\": \"PointLight\",\n");
}

double Light::intensityAt(World &w, Tuple point)
{
    switch(this->type)
    {
    case POINT_LIGHT:
    default:
        return (w.isShadowed(point, this->position))?0.0:1.0;

    case AREA_LIGHT:
        double total = 0.0;
        uint32_t v, u;
        for(v = 0; v < this->vSteps; v++)
        {
            for(u = 0; u < this->uSteps; u++)
            {
                if (!w.isShadowed(point, this->pointOnLight(u, v)))
                {
                    total = total + 1.0;
                }
            }
        }
        return total / this->samples;
        break;
    }
}

Tuple Light::pointOnLight(uint32_t u, uint32_t v)
{
    if (this->jitter)
    {
        /* For some reason, for the test to pass, I need to get the sequence for V first, then U contrary to what
         * the bonus chapter says
         */
        return this->corner +
               this->vVec * (v + this->jitterBy.next()) +
               this->uVec * (u + this->jitterBy.next());
    }
    return this->corner + this->uVec * (u + 0.5) + this->vVec * (v + 0.5);
}