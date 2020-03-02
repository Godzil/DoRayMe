/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Light header
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#ifndef DORAYME_LIGHT_H
#define DORAYME_LIGHT_H

#include <tuple.h>
#include <colour.h>
#include <renderstat.h>
#include <sequence.h>
#include <stdio.h>

class World;

enum LightType
{
    POINT_LIGHT = 0,
    AREA_LIGHT,

};

class Light
{
public:
    Colour intensity;
    Tuple position;
    LightType type;

    /* For area light */
    Tuple corner;
    Tuple uVec;
    Tuple vVec;
    uint32_t samples;
    uint32_t uSteps;
    uint32_t vSteps;
    bool jitter;
    Sequence jitterBy;

public:
    Light(LightType type = POINT_LIGHT, Tuple position=Point(0, 0, 0),
          Colour intensity=Colour(1, 1, 1)) : type(type), position(position), intensity(intensity)
          { stats.addLight(); };
    Light(LightType type, Tuple corner, Tuple fullUVec, uint32_t uSteps, Tuple fullVVec, uint32_t vSteps,
            Colour intensity, bool jitter = false): type(type), corner(corner), uVec(fullUVec / uSteps), uSteps(uSteps),
            vVec(fullVVec / vSteps), vSteps(vSteps), intensity(intensity), jitter(jitter)
    {
        this->samples = this->vSteps * this->uSteps;
        this->position = this->corner + ((fullUVec + fullVVec) / 2);
        stats.addLight();
    };
    double intensityAt(World &w, Tuple point);

    bool operator==(const Light &b) const { return this->intensity == b.intensity &&
                                                   this->position == b.position &&
                                                   this->type == b.type; };

    Tuple pointOnLight(uint32_t u, uint32_t v);

    void dumpMe(FILE *fp);
};

#endif /* DORAYME_LIGHT_H */
