/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Hw3file implementation
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
/* Don't build for now */
#if 0
/* This file is parsing a text format from another raytracer I made in the past. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <math.h>

#define IS_CMD(_cmd) (strncmp(buffer, _cmd, sizeof(_cmd)) == 0)

typedef void (*cmdFunc)(scene *sc, uint32_t curLine, char *first, float argv[15]);

typedef struct cmd_def
{
    const char *name;
    int8_t numparam; /* -1 == one string, else >0 = number of argv */
    cmdFunc f;
} cmd_def;

void cmdCamera   (scene *sc, uint32_t curLine, char *first, float argv[15])
{
    sc->cam.seteye(point(argv[0], argv[1], argv[2]));
    sc->cam.setat(point(argv[3], argv[4], argv[5]));
    sc->cam.setup(vector(argv[6], argv[7], argv[8]));
    sc->cam.setfovy(argv[9]);
}

void cmdSphere   (scene *sc, uint32_t curLine, char *first, float argv[15])
{
    /* Instanciate a sphere */
    sphere *sp     = new sphere(point(argv[0], argv[1], argv[2]), argv[3], sc->getMatrix());
    sp->ambient    = sc->ambient;
    sp->diffuse    = sc->diffuse;
    sp->specular   = sc->specular;
    sp->emission   = sc->emission;
    sp->shininess  = sc->shininess;
    sp->sourceLine = curLine;
    sc->o[sc->o_count] = sp;
    sc->o_count++;
}

void cmdCube     (scene *sc, uint32_t curLine, char *first, float argv[15])
{
}

#if 0
void cmdMaxVerts (scene *sc, uint32_t curLine, char *first, float argv[15])
{
    sc->vertexCount = (uint32_t) argv[0];
    sc->vertex = new point[sc->vertexCount];
    sc->curVertex = 0;
}

void cmdMaxVertN (scene *sc, uint32_t curLine, char *first, float argv[15])
{
    /* ignore for now */
}

void cmdVertex   (scene *sc, uint32_t curLine, char *first, float argv[15])
{
    sc->vertex[sc->curVertex].set(argv[0], argv[1], argv[2]);
    sc->curVertex++;
}

void cmdVertexN  (scene *sc, uint32_t curLine, char *first, float argv[15])
{
    /* ignore for now */
}

void cmdTri      (scene *sc, uint32_t curLine, char *first, float argv[15])
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

void cmdTriN     (scene *sc, uint32_t curLine, char *first, float argv[15])
{
    /* ignore for noz */
}
#endif

void cmdTrans    (scene *sc, uint32_t curLine, char *first, float argv[15])
{
    matrix m;
    m.translation(argv[0], argv[1], argv[2]);
    sc->applyTransform(m);
}

void cmdRotate   (scene *sc, uint32_t curLine, char *first, float argv[15])
{
    matrix m;
    vector axis;
    axis.set(argv[0], argv[1], argv[2]);
    m.rotation(axis, argv[3]);
    sc->applyTransform(m);
}

void cmdScale    (scene *sc, uint32_t curLine, char *first, float argv[15])
{
    matrix m;
    m.scale(argv[0], argv[1], argv[2]);
    sc->applyTransform(m);
}

void cmdPushT    (scene *sc, uint32_t curLine, char *first, float argv[15])
{
    sc->pushMatrix();
}

void cmdPopT     (scene *sc, uint32_t curLine, char *first, float argv[15])
{
    sc->popMatrix();
}

#if 0
void cmdLDire    (scene *sc, uint32_t curLine, char *first, float argv[15])
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
#endif

void cmdLPoint   (scene *sc, uint32_t curLine, char *first, float argv[15])
{
    /* create point light */
    light *cur = new light();

    cur->type = LIGHT_POINT;
    cur->attenuation = sc->attenuation;

    cur->position.set(argv[0], argv[1], argv[2]);
    cur->lightcolor.set(argv[3], argv[4], argv[5]);
    sc->l[sc->l_count] = cur;
    sc->l_count++;
}

#if 0
void cmdAtten    (scene *sc, uint32_t curLine, char *first, float argv[15])
{
    sc->attenuation = vector(argv[0], argv[1], argv[2]);
}
#endif

void cmdAmbient  (scene *sc, uint32_t curLine, char *first, float argv[15])
{
    sc->ambient = color(argv[0], argv[1], argv[2]);
}

void cmdDiffuse  (scene *sc, uint32_t curLine, char *first, float argv[15])
{
    sc->diffuse = color(argv[0], argv[1], argv[2]);
}

void cmdSpecular (scene *sc, uint32_t curLine, char *first, float argv[15])
{
    sc->specular = color(argv[0], argv[1], argv[2]);
}

void cmdShine    (scene *sc, uint32_t curLine, char *first, float argv[15])
{
    sc->shininess = argv[0];
}

void cmdEmission (scene *sc, uint32_t curLine, char *first, float argv[15])
{
    sc->emission = color(argv[0], argv[1], argv[2]);
}

cmd_def commandList[] =
        {
                /* Camera                         */
                { "camera",       10, cmdCamera   },
                /* Geometry                       */
                { "sphere",        4, cmdSphere   },
                //{ "maxverts",      1, cmdMaxVerts },
                //{ "maxvertnorms",  1, cmdMaxVertN },
                //{ "vertex",        3, cmdVertex   },
                //{ "vertexnormal",  6, cmdVertexN  },
                //{ "tri",           3, cmdTri      },
                //{ "trinormal",     3, cmdTriN     },
                //{ "cube",          1, cmdCube     },
                /* transformation                 */
                { "translate",     3, cmdTrans    },
                { "rotate",        4, cmdRotate   },
                { "scale",         3, cmdScale    },
                { "pushTransform", 0, cmdPushT    },
                { "popTransform",  0, cmdPopT     },
                /* Lights                         */
                //{ "directional",   6, cmdLDire    },
                { "point",         6, cmdLPoint   },
                //{ "attenuation",   3, cmdAtten    },
                /* Materials */
                { "ambient",       3, cmdAmbient  },
                { "diffuse",       3, cmdDiffuse  },
                { "specular",      3, cmdSpecular },
                { "shininess",     1, cmdShine    },
                { "emission",      3, cmdEmission },
        };
#define CMD_COUNT (sizeof(commandList) / sizeof(cmd_def))


scene *readfile::read(char *filename)
{
    FILE *fp;
    scene *sc = new scene;
    if (sc != NULL)
    {
        fp = fopen(filename, "rt");
        if (fp == NULL)
        {
            delete sc;
            sc = NULL;
        }
        else
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
                    continue; /* Ingore empty line or commented lines */
                //printf("::%d:> %s", strlen(buffer), buffer);
                for (i = 0; i < CMD_COUNT; i++)
                {
                    if (strncmp(buffer, commandList[i].name, strlen(commandList[i].name)) == 0)
                    {
                        char first[512];
                        float value[15];
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
                                sc = NULL;
                                goto exit;
                            }
                        }
                        commandList[i].f(sc, line, first, value);
                        break;
                    }
                }
            }
#ifdef USE_OCTREE
            sc->createOctree();
#endif
        }
    }

exit:
    return sc;
}

#endif