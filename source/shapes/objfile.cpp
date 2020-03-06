/*
 *  DoRayMe - a quick and dirty Raytracer
 *  OBJ File implementation
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <tuple.h>
#include <ray.h>
#include <shape.h>
#include <objfile.h>
#include <math_helper.h>
#include <group.h>

#define MIN_ALLOC (2)
#define DEFAULT_GROUP (0)

OBJFile::OBJFile() : Shape(SHAPE_OBJFILE), ignoredLines(0)
{
    stats.addOBJFile();

    this->allocatedFaceGroupCount = MIN_ALLOC;
    this->faceGroupList = (Shape **)calloc(sizeof(Shape *), MIN_ALLOC);
    this->faceGroupCount = 0;

    this->allocatedVertexCount = MIN_ALLOC;
    this->vertexList = (Tuple **)calloc(sizeof(Tuple *), MIN_ALLOC);
    this->vertexCount = 0;

    /* There is always a default group */
    this->addGroup(new Group());
};

OBJFile::OBJFile(const char *filepath) : OBJFile()
{
    FILE *fp;
    size_t fileSize;
    char *fileBuff;
    fp = fopen(filepath, "rt");
    if (fp)
    {
        fseek(fp, 0, SEEK_END);
        fileSize = ftell(fp);
        fileBuff = (char *)calloc(fileSize, 1);
        fseek(fp, 0, SEEK_SET);
        fileSize = fread(fileBuff, 1, fileSize, fp);
        fclose(fp);

        this->parseOBJFile(fileBuff);

        free(fileBuff);
    }
    else
    {
        printf("ERROR: Can't open/find the file '%s'.\n", filepath);
    }
}

void OBJFile::addGroup(Shape *group)
{
    if ((this->faceGroupCount + 1) > this->allocatedFaceGroupCount)
    {
        this->allocatedFaceGroupCount *= 2;
        this->faceGroupList = (Shape **)realloc(this->faceGroupList, sizeof(Shape **) * this->allocatedFaceGroupCount);
    }

    group->parent = this;
    group->updateTransform();

    this->faceGroupList[this->faceGroupCount++] = group;

    this->bounds | group->getBounds();
}

void OBJFile::addVertex(Tuple *vertex)
{
    if ((this->vertexCount + 1) > this->allocatedVertexCount)
    {
        this->allocatedVertexCount *= 2;
        this->vertexList = (Tuple **)realloc(this->vertexList, sizeof(Tuple **) * this->allocatedVertexCount);
    }

    this->vertexList[this->vertexCount++] = vertex;
}

Intersect OBJFile::intersect(Ray r)
{
    Intersect ret;
    int i, j;
    if (this->faceGroupCount > 0)
    {
        if (this->bounds.intesectMe(r))
        {
            for (i = 0 ; i < this->faceGroupCount ; i++)
            {
                Intersect xs = this->faceGroupList[i]->intersect(r);
                if (xs.count() > 0)
                {
                    for (j = 0 ; j < xs.count() ; j++)
                    {
                        ret.add(xs[j]);
                    }
                }
            }
        }
    }
    return ret;
}

Intersect OBJFile::localIntersect(Ray r)
{
    return Intersect();
}

Tuple OBJFile::localNormalAt(Tuple point)
{
    return Vector(0, 1, 0);
}

BoundingBox OBJFile::getLocalBounds()
{
    return this->bounds;
}

BoundingBox OBJFile::getBounds()
{
    if (this->bounds.isEmpty()) { this->updateBoundingBox(); }
    return this->bounds;
}

void OBJFile::updateBoundingBox()
{
    int i;
    this->bounds.reset();

    for(i = 0; i < this->faceGroupCount; i++)
    {
        if (this->faceGroupList[i]->haveFiniteBounds())
        {
            BoundingBox objB = this->faceGroupList[i]->getBounds();
            this->bounds | objB;
        }
    }
}

void OBJFile::updateTransform()
{
    int i;

    Shape::updateTransform();
    for (i = 0 ; i < this->faceGroupCount ; i++)
    {
        this->faceGroupList[i]->updateTransform();
    }

    /* Once the full stack being notified of the changes, let's update the
     * bounding box
     */
    this->updateBoundingBox();
}

void OBJFile::dumpMe(FILE * fp)
{

}

#define MAX_LINE_LENGTH (512)
/* Here start the fun! */
int OBJFile::parseOBJFile(const char *content)
{
    /* I don't think we will handle lines of more than 512 characters... */
    char lineBuff[MAX_LINE_LENGTH];
    uint32_t currentLineNum = 1;

    /* Need to process line by line */
    const char *bufferPos = content;
    const char *lineNewline;
    while(*bufferPos != '\0')
    {
        uint32_t lineLength;
        lineNewline = strchr(bufferPos, '\n');
        if (lineNewline == nullptr)
        {
            /* We are on the last line */
            lineLength = strlen(bufferPos);
        }
        else
        {
            lineLength = (lineNewline - bufferPos);
        }
        if (lineLength >= MAX_LINE_LENGTH)
        {
            printf("ERROR: Line %d is too long! (%d)\n", currentLineNum, lineLength);
            return -1;
        }
        memset(lineBuff, 0, MAX_LINE_LENGTH);
        strncpy(lineBuff, bufferPos, lineLength);

        this->parseLine(lineBuff);

        bufferPos += lineLength + 1;
        currentLineNum++;
    }
    return 0;
}

#define MAX_ARGS (15)

/* Parse the line into a couple ofr argc/argv using space as argument separator */
void OBJFile::parseLine(char *line)
{
    char *argv[MAX_ARGS];
    uint32_t argc = 0;

    char *buffer = line;
    uint32_t lineLength = strlen(line);
    uint32_t linePos = 0;

    /* First argument */
    argv[argc++] = line;

    while(linePos < lineLength)
    {
        char *next = strchr(buffer, ' ');
        if (next != nullptr)
        {
            *next = '\0';
            linePos = next - line;
            buffer = next + 1;
            argv[argc++] = buffer;
        }
        else
        {
            linePos = lineLength;
        }
    }

    if (this->execLine(argc, argv))
    {
        this->ignoredLines++;
    }
}

/* Actually execute the line */
int OBJFile::execLine(int argc, char *argv[])
{
    return 1;
}