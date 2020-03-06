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
    CUBIC_MAP
};

class TextureMap : public Pattern
{
private:
    TextureMapType type;
    UVPattern *pattern;
    UVPattern *frontPat, *leftPat, *rightPat, *backPat, *upPat, *downPat;
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

    static void planarMap(Tuple point, double &u, double &v) {
        u = modulo(point.x, 1.0);
        v = modulo(point.z, 1.0);
    }

    static void cylindricalMap(Tuple point, double &u, double &v) {
        /* Let's get the azimuthal angle, same as with the spherical mapping */
        double theta = atan2(point.x , point.z);
        double raw_u = theta / (2 * M_PI);

        u = 1 - (raw_u + 0.5);
        v = modulo(point.y, 1.0);
    }

    enum CubeFaces {
        CUBE_LEFT,
        CUBE_RIGHT,
        CUBE_FRONT,
        CUBE_BACK,
        CUBE_UP,
        CUBE_DOWN,
    };

    static CubeFaces faceFromPoint(Tuple point) {
        double abs_x = fabs(point.x);
        double abs_y = fabs(point.y);
        double abs_z = fabs(point.z);

        double coord = max3(abs_x, abs_y, abs_z);

        if (coord == point.x) { return CUBE_RIGHT; }
        if (coord == -point.x) { return CUBE_LEFT; }
        if (coord == point.y) { return CUBE_UP; }
        if (coord == -point.y) { return CUBE_DOWN; }
        if (coord == point.z) { return CUBE_FRONT; }

        return CUBE_BACK;
    }

    static void cubeUBFront(Tuple point, double &u, double &v) {
        u = modulo(point.x + 1, 2.0) / 2.0;
        v = modulo(point.y + 1, 2.0) / 2.0;
    }

    static void cubeUBBack(Tuple point, double &u, double &v) {
        u = modulo(1 - point.x, 2.0) / 2.0;
        v = modulo(point.y + 1, 2.0) / 2.0;
    }

    static void cubeUBLeft(Tuple point, double &u, double &v) {
        u = modulo(point.z + 1, 2.0) / 2.0;
        v = modulo(point.y + 1, 2.0) / 2.0;
    }

    static void cubeUBRight(Tuple point, double &u, double &v) {
        u = modulo(1 - point.z, 2.0) / 2.0;
        v = modulo(point.y + 1, 2.0) / 2.0;
    }

    static void cubeUBUp(Tuple point, double &u, double &v) {
        u = modulo(point.x + 1, 2.0) / 2.0;
        v = modulo(1 - point.z, 2.0) / 2.0;
    }

    static void cubeUBDown(Tuple point, double &u, double &v) {
        u = modulo(point.x + 1, 2.0) / 2.0;
        v = modulo(point.z + 1, 2.0) / 2.0;
    }

    void setCubePattern(UVPattern *front, UVPattern *left, UVPattern *right,
                        UVPattern *back, UVPattern *up, UVPattern *down)
    {
        this->frontPat = front;
        this->leftPat = left;
        this->rightPat = right;
        this->backPat = back;
        this->upPat = up;
        this->downPat = down;
    }

    Colour patternAt(Tuple point)
    {
        double u,v;
        if (this->type == CUBIC_MAP)
        {
            CubeFaces face = TextureMap::faceFromPoint(point);
            UVPattern *facePat;
            switch(face)
            {
            default:
            case CUBE_LEFT:  facePat = this->leftPat;  TextureMap::cubeUBLeft(point, u, v);  break;
            case CUBE_RIGHT: facePat = this->rightPat; TextureMap::cubeUBRight(point, u, v); break;
            case CUBE_FRONT: facePat = this->frontPat; TextureMap::cubeUBFront(point, u, v); break;
            case CUBE_BACK:  facePat = this->backPat;  TextureMap::cubeUBBack(point, u, v);  break;
            case CUBE_UP:    facePat = this->upPat;    TextureMap::cubeUBUp(point, u, v);    break;
            case CUBE_DOWN:  facePat = this->downPat;  TextureMap::cubeUBDown(point, u, v);  break;
            }

            return facePat->uvPatternAt(u, v);
        }
        else
        {
            switch (this->type)
            {
            default:
            case SPHERICAL_MAP:
                this->sphericalMap(point, u, v);
                break;
            case PLANAR_MAP:
                this->planarMap(point, u, v);
                break;

            case CYLINDRICAL_MAP:
                this->cylindricalMap(point, u, v);
                break;
            }

            return this->pattern->uvPatternAt(u, v);
        }
    }

    void dumpMe(FILE *fp) {
        fprintf(fp, "\"Type\": \"TextureMap\",\n");
        Pattern::dumpMe(fp);
    }
};

#endif /* DORAYME_TEXTUREMAP_H */
