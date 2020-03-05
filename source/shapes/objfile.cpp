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

Intersect OBJFile::localIntersect(Ray r)
{

}

Tuple OBJFile::localNormalAt(Tuple point)
{

}

BoundingBox OBJFile::getLocalBounds()
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
            printf("ERROR: Line %d is too long! (%d)\n", currentLineNum);
        }
        memset(lineBuff, 0, MAX_LINE_LENGTH);
        strncpy(lineBuff, bufferPos, lineLength);

        printf("line %d = %s\n", currentLineNum, lineBuff);

        bufferPos += lineLength + 1;
        currentLineNum++;
    }



}