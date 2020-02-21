/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Intersection implementation
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <intersection.h>
#include <shape.h>
#include <list.h>

Computation Intersection::prepareComputation(Ray r, Intersect *xs)
{
    double n1 = 1.0;
    double n2 = 1.0;

    Tuple hitP = r.position(this->t);
    Tuple normalV = this->object->normalAt(hitP);
    Tuple eyeV = -r.direction;
    bool inside = false;

    if (normalV.dot(eyeV) < 0)
    {
        inside = true;
        normalV = -normalV;
    }

    Tuple overHitP = hitP + normalV * getEpsilon();
    Tuple underHitP = hitP - normalV * getEpsilon();
    Tuple reflectV = r.direction.reflect(normalV);

    if (xs != nullptr)
    {
        List containers;
        int j, k;

        for(j = 0; j < xs->count(); j++)
        {
            Intersection i = (*xs)[j];
            if (*this == i)
            {
                if (!containers.isEmpty())
                {
                    n1 = containers.last()->material.refractiveIndex;
                }
            }

            if (containers.doesInclude(i.object))
            {
                containers.remove(i.object);
            }
            else
            {
                containers.append(i.object);
            }

            if (*this == i)
            {
                if (!containers.isEmpty())
                {
                    n2 = containers.last()->material.refractiveIndex;
                }

                /* End the loop */
                break;
            }
        }
    }

    return Computation(this->object,
                       this->t,
                       hitP,
                       eyeV,
                       normalV,
                       overHitP,
                       inside,
                       reflectV,
                       n1,
                       n2,
                       underHitP);
}