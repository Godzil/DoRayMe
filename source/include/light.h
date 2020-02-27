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

enum LightType
{
    POINT_LIGHT = 0,
};

class Light
{
public:
    Colour intensity;
    Tuple position;
    LightType type;

public:
    Light(LightType type = POINT_LIGHT, Tuple position=Point(0, 0, 0),
          Colour intensity=Colour(1, 1, 1)) : type(type), position(position), intensity(intensity)
          { stats.addLight(); };

    bool operator==(const Light &b) const { return this->intensity == b.intensity &&
                                                   this->position == b.position &&
                                                   this->type == b.type; };
};

#endif /* DORAYME_LIGHT_H */
