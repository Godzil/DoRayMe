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
#include <triangle.h>

#define MIN_ALLOC (2)
#define DEFAULT_GROUP (0)

OBJFile::OBJFile() : Shape(SHAPE_OBJFILE), ignoredLines(0)
{
    stats.addOBJFile();

    this->allocatedFaceGroupCount = MIN_ALLOC;
    this->faceGroupList = (Group **)calloc(sizeof(Group **), MIN_ALLOC);
    this->faceGroupCount = 0;

    this->allocatedVertexCount = MIN_ALLOC;
    this->vertexList = (Point **)calloc(sizeof(Point **), MIN_ALLOC);
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

void OBJFile::addGroup(Group *group)
{
    if ((this->faceGroupCount + 1) > this->allocatedFaceGroupCount)
    {
        this->allocatedFaceGroupCount *= 2;
        this->faceGroupList = (Group **)realloc(this->faceGroupList, sizeof(Group **) * this->allocatedFaceGroupCount);
    }

    group->parent = this;
    group->updateTransform();

    this->faceGroupList[this->faceGroupCount++] = group;

    this->bounds | group->getBounds();
}

void OBJFile::addVertex(Point *vertex)
{
    if ((this->vertexCount + 1) > this->allocatedVertexCount)
    {
        this->allocatedVertexCount *= 2;
        this->vertexList = (Point **)realloc(this->vertexList, sizeof(Point **) * this->allocatedVertexCount);
    }

    this->vertexList[this->vertexCount++] = vertex;
}

Intersect OBJFile::intersect(Ray r)
{
    Intersect ret;
    int i, j;
    if (this->faceGroupCount > 0)
    {
        //if (this->bounds.intesectMe(r))
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
    int i;
    fprintf(fp, "\"Type\": \"OBJFile\",\n");
    fprintf(fp, "\"Objects\": {\n");
    for(i = 0; i < this->faceGroupCount; i++)
    {
        fprintf(fp, "\"%d\": {\n", i);
        this->faceGroupList[i]->dumpMe(fp);
        fprintf(fp, "},\n");
    }
    fprintf(fp, "},\n");

    Shape::dumpMe(fp);
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

        this->parseLine(lineBuff, currentLineNum);

        bufferPos += lineLength + 1;
        currentLineNum++;
    }
    return 0;
}

#define MAX_ARGS (15)

/* Parse the line into a couple ofr argc/argv using space as argument separator */
void OBJFile::parseLine(char *line, uint32_t currentLine)
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
            /* Skip empty strings as it mean multiple spaces */
            if (strlen(buffer) > 0)
            {
                argv[argc++] = buffer;
            }
        }
        else
        {
            linePos = lineLength;
        }
    }

    if (this->execLine(argc, argv, currentLine))
    {
        this->ignoredLines++;
    }
}

/* Actually execute the line */
int OBJFile::execLine(int argc, char *argv[], uint32_t currentLine)
{
    int ret = 1;
    if (strncmp(argv[0], "v", 1) == 0)
    {
        /* Vertice entry */
        if (argc != 4)
        {
            printf("ERROR: Malformed file at line %d: Vertices expect 3 parameters!\n", currentLine);
        }
        else
        {
            this->addVertex(new Point(atof(argv[1]), atof(argv[2]), atof(argv[3])));
            ret = 0;
        }
    }
    else if (strncmp(argv[0], "f", 1) == 0)
    {
        /* Vertice entry */
        if (argc == 4)
        {
            Shape *t = new Triangle(this->vertices(atoi(argv[1])),
                                    this->vertices(atoi(argv[2])),
                                    this->vertices(atoi(argv[3])));
            this->faceGroupList[this->faceGroupCount - 1]->addObject(t);
            ret = 0;
        }
        else if (argc > 4)
        {
            int i;
            for(i = 2; i < (argc - 1); i++)
            {
                Shape *t = new Triangle(this->vertices(atoi(argv[1])),
                                        this->vertices(atoi(argv[i])),
                                        this->vertices(atoi(argv[i+1])));
                this->faceGroupList[this->faceGroupCount - 1]->addObject(t);
            }
            ret = 0;
        }
        else
        {
            printf("ERROR: Malformed file at line %d: Too few/many parameters!\n", currentLine);
        }
    }
    else if (strncmp(argv[0], "g", 1) == 0)
    {
        if (argc == 2)
        {
            this->addGroup(new Group());
        }
        else
        {
            printf("ERROR: Malformed file at line %d: Too few/many parameters!\n", currentLine);
        }
    }
    return ret;
}