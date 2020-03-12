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

double Computation::schlick()
{
    /* Find the cos of the angle betzeen the eye and normal vector */
    double cos = this->eyeVector.dot(this->normalVector);
    double r0;
    /* Total internal reflection can only occur when n1 > n2 */
    if (this->n1 > this->n2)
    {
    double n, sin2_t;
    n = this->n1 / this->n2;
    sin2_t = (n * n) * (1.0 - (cos * cos));
    if (sin2_t > 1.0)
    {
    return 1.0;
    }
    /* Compute the cos of theta */
    cos = sqrt(1.0 - sin2_t);
    }


    r0 = ((this->n1 - this->n2) / (this->n1 + this->n2));
    r0 = r0 * r0;

    return r0 + (1 - r0) *  ((1 - cos)*(1 - cos)*(1 - cos)*(1 - cos)*(1 - cos));
};

Computation Intersection::prepareComputation(Ray r, Intersect *xs)
{
    double n1 = 1.0;
    double n2 = 1.0;

    Tuple hitP = r.position(this->t);
    Tuple normalV;

    if (xs != nullptr)
    {
        Intersection hit = xs->hit();
        normalV = this->object->normalAt(hitP, &hit);
    }
    else
    {
        normalV = this->object->normalAt(hitP, nullptr);
    }

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

    /* If the hit object is not transparent, there is no need to do that. I think .*/
    if ((xs != nullptr) && (xs->hit().object->getMaterial()->transparency > 0))
    {
        List containers;
        int j;

        for (j = 0 ; j < xs->count() ; j++)
        {
            Intersection i = ( *xs )[j];
            if (*this == i)
            {
                if (!containers.isEmpty())
                {
                    n1 = containers.last()->getMaterial()->refractiveIndex;
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
                    n2 = containers.last()->getMaterial()->refractiveIndex;
                }

                /* End the loop */
                break;
            }
        }
    }

    Material *m = this->object->getMaterial();

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
                       underHitP,
                       m);
}
