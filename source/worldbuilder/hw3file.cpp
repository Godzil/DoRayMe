/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Hw3file implementation
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
/* Don't build for now */

/* This file is parsing a text format from another raytracer I made in the past. */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include <worldbuilder.h>
#include <sphere.h>
#include <matrix.h>
#include <transformation.h>

#define IS_CMD(_cmd) (strncmp(buffer, _cmd, sizeof(_cmd)) == 0)

typedef void (*cmdFunc)(Hw3File *w, uint32_t curLine, double argv[15]);

typedef struct cmd_def
{
    const char *name;
    int8_t numparam; /* -1 == one string, else >0 = number of argv */
    cmdFunc f;
} cmd_def;

static void cmdCamera   (Hw3File *w, uint32_t curLine, double argv[15])
{
    w->cam = viewTransform(Point(argv[0], argv[1], argv[2]),
                                      Point(argv[3], argv[4], argv[5]),
                                      Vector(argv[6], argv[7], argv[8]));

    w->camFoV = deg_to_rad(argv[9]);
}

/* 0: X, 1: Y, 2: Z
 * 3: Radius
 */
static void cmdSphere   (Hw3File *w, uint32_t curLine, double argv[15])
{
    printf("Adding a sphere...\n");
    /* Instanciate a sphere */
    Sphere *shape  = new Sphere();

    Matrix pos = translation(argv[0], argv[1], argv[2]) * scaling(argv[3], argv[3], argv[3]);

    shape->setTransform(w->getTransformMatrix() * pos);
    
    shape->material.ambient = w->currentAmbient;
    shape->material.reflective = w->currentReflective;
    shape->material.shininess = w->currentShininess;
    shape->material.specular = w->currentSpecular;
    shape->material.diffuse = w->currentDiffuse;
    shape->material.colour = w->currentColour;
    shape->material.transparency = w->currentTransparency;
    shape->material.refractiveIndex = w->currentRefIndex;

    w->addObject(shape);
}

static void cmdCube     (Hw3File *w, uint32_t curLine, double argv[15])
{
}

static void cmdTrans    (Hw3File *w, uint32_t curLine, double argv[15])
{
    Matrix m = translation(argv[0], argv[1], argv[2]);
    w->applyTransformMatrix(m);
}

static void cmdRotate   (Hw3File *w, uint32_t curLine, double argv[15])
{
    Matrix m = Matrix4().identity();
    if (argv[2] != 0)
    {
        m = m * rotationZ(argv[3]);
    }
    if (argv[1] != 0)
    {
        m = m * rotationY(argv[3]);
    }
    if (argv[0] != 0)
    {
        m = m * rotationX(argv[3]);
    }

    w->applyTransformMatrix(m);
}

static void cmdScale    (Hw3File *w, uint32_t curLine, double argv[15])
{
    Matrix m = scaling(argv[0], argv[1], argv[2]);

    w->applyTransformMatrix(m);
}

static void cmdPushT    (Hw3File *w, uint32_t curLine, double argv[15])
{
    w->pushTransformMatrix();
}

static void cmdPopT     (Hw3File *w, uint32_t curLine, double argv[15])
{
    w->popTransformMatrix();
}

static void cmdLPoint   (Hw3File *w, uint32_t curLine, double argv[15])
{
    /* create point light */
    Light *l = new Light(POINT_LIGHT, Point(argv[0], argv[1], argv[2]), Colour(argv[3], argv[4], argv[5]));

    w->addLight(l);
}

static void cmdAmbient  (Hw3File *w, uint32_t curLine, double argv[15])
{
    //w->currentAmbient = (argv[0] + argv[1] + argv[2]) / 3;
    w->currentColour = Colour(argv[0], argv[1], argv[2]);
}

static void cmdColour  (Hw3File *w, uint32_t curLine, double argv[15])
{
    w->currentColour = Colour(argv[0], argv[1], argv[2]);
}

static void cmdDiffuse  (Hw3File *w, uint32_t curLine, double argv[15])
{
    w->currentDiffuse = (argv[0] + argv[1] + argv[2]) / 3;
}

static void cmdSpecular (Hw3File *w, uint32_t curLine, double argv[15])
{
    w->currentSpecular = (argv[0] + argv[1] + argv[2]) / 3;
}

static void cmdShine    (Hw3File *w, uint32_t curLine, double argv[15])
{
    w->currentReflective = argv[0];
}

static void cmdEmission (Hw3File *w, uint32_t curLine, double argv[15])
{
    w->currentEmission = (argv[0] + argv[1] + argv[2]) / 3;
}

#if 0
static void cmdLDire    (Hw3File *w, uint32_t curLine, double argv[15])
{
    /* create directional light */
    light *cur = new light();

    cur->type = LIGHT_DIRECTIONAL;
    cur->attenuation = sc->attenuation;

    cur->position.set(argv[0], argv[1], argv[2]);
    cur->lightcolor.set(argv[3], argv[4], argv[5]);

    sc->l[sc->l_count] = cur;
    sc->l_count++;
}

static void cmdAtten    (Hw3File *w, uint32_t curLine, double argv[15])
{
    sc->attenuation = Vector(argv[0], argv[1], argv[2]);
}

static void cmdMaxVerts (Hw3File *w, uint32_t curLine, double argv[15])
{
    sc->vertexCount = (uint32_t) argv[0];
    sc->vertex = new point[sc->vertexCount];
    sc->curVertex = 0;
}

static void cmdMaxVertN (Hw3File *w, uint32_t curLine, double argv[15])
{
    /* ignore for now */
}

static void cmdVertex   (Hw3File *w, uint32_t curLine, double argv[15])
{
    sc->vertex[sc->curVertex].set(argv[0], argv[1], argv[2]);
    sc->curVertex++;
}

static void cmdVertexN  (Hw3File *w, uint32_t curLine, double argv[15])
{
    /* ignore for now */
}

static void cmdTri      (Hw3File *w, uint32_t curLine, double argv[15])
{
    /* arg are vertex numbers */
    triangle *tr   = new triangle(sc->vertex[(int)argv[0]], sc->vertex[(int)argv[1]], sc->vertex[(int)argv[2]], sc->getMatrix());
    tr->ambient    = sc->ambient;
    tr->diffuse    = sc->diffuse;
    tr->specular   = sc->specular;
    tr->emission   = sc->emission;
    tr->shininess  = sc->shininess;
    tr->sourceLine = curLine;
    sc->o[sc->o_count] = tr;
    sc->o_count++;
}
#endif

static cmd_def commandList[] =
{
    /* Camera                         */
    {"camera",        10, cmdCamera},
    /* Geometry                       */
    {"sphere",        4,  cmdSphere},
    //{ "maxverts",      1, cmdMaxVerts },
    //{ "maxvertnorms",  1, cmdMaxVertN },
    //{ "vertex",        3, cmdVertex   },
    //{ "vertexnormal",  6, cmdVertexN  },
    //{ "tri",           3, cmdTri      },
    //{ "trinormal",     3, cmdTriN     },
    //{ "cube",          1, cmdCube     },
    /* transformation                 */
    {"translate",     3,  cmdTrans},
    {"rotate",        4,  cmdRotate},
    {"scale",         3,  cmdScale},
    {"pushTransform", 0,  cmdPushT},
    {"popTransform",  0,  cmdPopT},
    /* Lights                         */
    //{ "directional",   6, cmdLDire    },
    {"point",         6,  cmdLPoint},
    //{ "attenuation",   3, cmdAtten    },
    /* Materials */
    {"color",         3,  cmdColour},
    {"ambient",       3,  cmdAmbient},
    {"diffuse",       3,  cmdDiffuse},
    {"specular",      3,  cmdSpecular},
    {"shininess",     1,  cmdShine},
    {"emission",      3,  cmdEmission},
};
#define CMD_COUNT (sizeof(commandList) / sizeof(cmd_def))


Hw3File::Hw3File(const char *filename) : transStackCount(0), currentColour(Colour(1, 1, 1)),
                                         currentEmission(0), currentShininess(200), currentAmbient(0.1),
                                         currentDiffuse(0.9), currentSpecular(0.9), camFoV(0)
{
    FILE *fp;

    this->popTransformMatrix();

    fp = fopen(filename, "rt");
    if (fp != NULL)
    {
        char buffer[512];
        int line = 0;
        while(!feof(fp))
        {
            uint32_t i;

            line++;

            memset(buffer, 0, 512);
            fgets(buffer, 512, fp);

            if ((buffer[0] == '#') || (strlen(buffer) < 2))
            {
                continue; /* Ingore empty line or commented lines */
            }

            for (i = 0; i < CMD_COUNT; i++)
            {
                if (strncmp(buffer, commandList[i].name, strlen(commandList[i].name)) == 0)
                {
                    char first[512];
                    double value[15];
                    if (commandList[i].numparam != 0)
                    {
                        size_t j;
                        int k = 0, l = 0;
                        char buff[512];
                        for(j = strlen(commandList[i].name); j < strlen(buffer); j++)
                        {
                            if (!isspace(buffer[j]))
                            {
                                buff[l++] = buffer[j];
                            }
                            else
                            {
                                buff[l] = 0;
                                l = 0;
                                if (k == 0)
                                {
                                    strcpy(first, buff);
                                }
                                if (strlen(buff) > 0)
                                {
                                    value[k++] = atof(buff);
                                }
                            }
                        }
                        if (k != abs(commandList[i].numparam))
                        {
                            printf("line %d malformed: given %d parameter, expected %d\n%s", line, k, abs(commandList[i].numparam), buffer);
                            goto exit;
                        }
                    }
                    commandList[i].f(this, line, value);
                    break;
                }
            }
        }
    }

exit:
    return;
}

Matrix Hw3File::getTransformMatrix()
{
    return this->transformStack[this->transStackCount];
}

void Hw3File::popTransformMatrix()
{
    if (this->transStackCount == 0)
    {
        this->transformStack[0] = Matrix4().identity();
    }
    else
    {
        this->transformStack[this->transStackCount] = Matrix4().identity();
        this->transStackCount --;
    }
}

void Hw3File::pushTransformMatrix()
{
    this->transStackCount ++;
    this->transformStack[this->transStackCount] = this->transformStack[this->transStackCount - 1];
}

void Hw3File::applyTransformMatrix(Matrix t)
{
    this->transformStack[this->transStackCount] = this->transformStack[this->transStackCount] * t;
}