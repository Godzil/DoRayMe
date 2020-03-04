/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Texture Map header
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */

#ifndef DORAYME_TEXTUREMAP_H
#define DORAYME_TEXTUREMAP_H

#include <math.h>
#include <tuple.h>
#include <uv_pattern.h>
#include <colour.h>
enum TextureMapType
{
    SPHERICAL_MAP,
    PLANAR_MAP,
    CYLINDRICAL_MAP,
};

class TextureMap : public Pattern
{
private:
    TextureMapType type;
    UVPattern *pattern;
public:
    TextureMap(TextureMapType type, UVPattern *pattern) : Pattern(Colour(0, 0, 0), Colour(0, 0, 0)),
                                                          type(type), pattern(pattern) { };

    static void sphericalMap(Tuple point, double &u, double &v) {
        /* First compute the azimuthal angle
         * -π < theta <= π
         * angle increases clockwise as viewed from above,
         * which is opposite of what we want, but we'll fix it later.
         */
        double theta = atan2(point.x, point.z);

        /* vec is the vector pointing from the sphere's origin (the world origin)
         * to the point, which will also happen to be exactly equal to the sphere's
         * radius.
         */
        Tuple vec = Vector(point.x, point.y, point.z);
        double radius = vec.magnitude();

        /* Let's compute the polar angle
         * 0 <= phi <= π
         */
        double phi = acos(point.y / radius);

        /* -0.5 < raw_u <= 0.5 */
        double raw_u = theta / (2 * M_PI);

        /* 0 <= u < 1
         * here's also where we fix the direction of u. Subtract it from 1,
         * so that it increases counterclockwise as viewed from above.
         */
        u = 1 - (raw_u + 0.5);

        /* We want v to be 0 at the south pole of the sphere,
         * and 1 at the north pole, so we have to "flip it over"
         * by subtracting it from 1.
         */
        v = 1 - phi / M_PI;
    }

    Colour patternAt(Tuple point)
    {
        double u,v;
        switch(this->type)
        {
        default:
        case SPHERICAL_MAP:
            this->sphericalMap(point, u, v);
            break;
        }

        return this->pattern->uvPatternAt(u, v);
    }

    void dumpMe(FILE *fp) {
        fprintf(fp, "\"Type\": \"TextureMap\",\n");
        Pattern::dumpMe(fp);
    }
};

#endif /* DORAYME_TEXTUREMAP_H */
