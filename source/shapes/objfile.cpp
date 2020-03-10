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
#include <smoothtriangle.h>

#define MIN_ALLOC (2)
#define DEFAULT_GROUP (0)

OBJFile::OBJFile() : Shape(Shape::OBJFILE), ignoredLines(0)
{
    stats.addOBJFile();

    this->allocatedVertexCount = MIN_ALLOC;
    this->vertexList = (Point **)calloc(sizeof(Point **), MIN_ALLOC);
    this->vertexCount = 0;

    this->allocatedVertexNormalCount = MIN_ALLOC;
    this->vertexNormalList = (Vector **)calloc(sizeof(Vector **), MIN_ALLOC);
    this->vertexNormalCount = 0;

    /* The base group */
    this->baseGroup = new Group(OBJ_DEFAULT_GROUP);
    this->currentGroup = this->baseGroup;
};

OBJFile::~OBJFile()
{
    int i;
    if (vertexCount > 0)
    {
        for(i = 0; i < vertexCount; i++)
        {
            delete this->vertexList[i];
            this->vertexList[i] = nullptr;
        }
    }
    free(this->vertexList);
    this->vertexList = nullptr;

    if (vertexNormalCount > 0)
    {
        for(i = 0; i < vertexNormalCount; i++)
        {
            delete this->vertexNormalList[i];
            this->vertexNormalList[i] = nullptr;
        }
    }
    free(this->vertexNormalList);
    this->vertexNormalList = nullptr;

    /* It is not our responsibility to clear the group object as this object may be destroyed before the
     * render is done
     */
}

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
        /* Add one byte to the size to make sure it is null terminated */
        fileBuff = (char *)calloc(fileSize + 1, 1);
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
    this->baseGroup->addObject(group);

    group->setParent(this);
    group->updateTransform();
    this->bounds | group->getBounds();

    this->currentGroup = group;
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

void OBJFile::addVertexNormal(Vector *vertexNormal)
{
    if ((this->vertexNormalCount + 1) > this->allocatedVertexNormalCount)
    {
        this->allocatedVertexNormalCount *= 2;
        this->vertexNormalList = (Vector **)realloc(this->vertexNormalList, sizeof(Vector **) * this->allocatedVertexNormalCount);
    }

    this->vertexNormalList[this->vertexNormalCount++] = vertexNormal;
}

Group *OBJFile::groups(const char *groupName)
{
    if (strncmp(groupName, this->baseGroup->getName(), strlen(groupName)) == 0)
    {
        return this->baseGroup;
    }

    int i;
    for(i = 0; i < this->baseGroup->getObjectCount(); i++)
    {
        Shape *cur = (*this->baseGroup)[i];

        if (cur->getType() == Shape::GROUP)
        {
            Group *curGrp = (Group *)cur;
            if (strncmp(groupName, curGrp->getName(), strlen(groupName)) == 0)
            {
                return curGrp;
            }
        }
    }

    /* Not found */
    return nullptr;
}

Intersect OBJFile::intersect(Ray r)
{
    return this->baseGroup->intersect(r);
}

bool OBJFile::includes(Shape *b)
{
    return this->baseGroup->includes(b);
}

Intersect OBJFile::localIntersect(Ray r)
{
    return Intersect();
}

Tuple OBJFile::localNormalAt(Tuple point, Intersection *hit)
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

    this->bounds | this->baseGroup->getBounds();
}

void OBJFile::updateTransform()
{
    int i;

    Shape::updateTransform();

    this->baseGroup->updateTransform();

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
    this->baseGroup->dumpMe(fp);
    fprintf(fp, "},\n");
    fprintf(fp, "\"Vertices\": {\n");
    for(i = 1; i < this->vertexCount + 1; i++)
    {
        fprintf(fp, "\"v[%d]\": { \"x\": %f, \"y\": %f, \"z\": %f },\n", i,
                    this->vertices(i).x, this->vertices(i).y, this->vertices(i).z);
    }
    fprintf(fp, "},\n");
    fprintf(fp, "\"NormalVertices\": {\n");
    for(i = 1; i < this->vertexNormalCount + 1; i++)
    {
        fprintf(fp, "\"vn[%d]\": { \"x\": %f, \"y\": %f, \"z\": %f },\n", i,
                this->verticesNormal(i).x, this->verticesNormal(i).y, this->verticesNormal(i).z);
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
    uint32_t totalLength = strlen(content);
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

        if ((bufferPos - content) >= totalLength)
        {
            /* We are past the length of the buffer, don't need to continue */
            break;
        }
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

static int parseFaceVertex(char *buf, uint32_t &v, uint32_t  &vt, uint32_t  &vn)
{
    uint32_t bufPos = 0;
    uint32_t lineLength = strlen(buf);
    vt = INT32_MAX;
    vn = INT32_MAX;
    int ret = 0;
    int token = 0;

    while(bufPos < lineLength)
    {
        char *next = strchr(buf, '/');
        if (next != nullptr)
        {
            *next = '\0';
            bufPos = next - buf;
        }
        else
        {
            bufPos = lineLength;
        }

        if (strlen(buf) > 0)
        {
            switch(token)
            {
            case 0:  v = atol(buf); break;
            case 1:  vt = atol(buf); break;
            case 2:  vn = atol(buf); break;
            default: printf("ERROR: Too many entry for a face vertice!"); ret = 1;
            }
        }
        buf = next + 1;
        token++;
    }

    return ret;
}

/* Actually execute the line */
int OBJFile::execLine(int argc, char *argv[], uint32_t currentLine)
{
    int ret = 1;
    if (strncmp(argv[0], "v", 2) == 0)
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
    else if (strncmp(argv[0], "vn", 3) == 0)
    {
        /* Vertice Normal entry */
        if (argc != 4)
        {
            printf("ERROR: Malformed file at line %d: Vertices normal expect 3 parameters!\n", currentLine);
        }
        else
        {
            this->addVertexNormal(new Vector(atof(argv[1]), atof(argv[2]), atof(argv[3])));
            ret = 0;
        }
    }
    else if (strncmp(argv[0], "f", 2) == 0)
    {
        /* Faces entry */
        int i;
        uint32_t v[MAX_ARGS], vt[MAX_ARGS], vn[MAX_ARGS];
        for(i = 1; i < argc; i++)
        {
            parseFaceVertex(argv[i], v[i], vt[i], vn[i]);
        }

        if (argc == 4)
        {
            Shape *t;
            if (vn[1] == INT32_MAX)
            {
                t = new Triangle(this->vertices(v[1]),
                                 this->vertices(v[2]),
                                 this->vertices(v[3]));
            }
            else
            {
                t = new SmoothTriangle(this->vertices(v[1]),
                                       this->vertices(v[2]),
                                       this->vertices(v[3]),
                                       this->verticesNormal(vn[1]),
                                       this->verticesNormal(vn[2]),
                                       this->verticesNormal(vn[3]));
            }
            this->currentGroup->addObject(t);
            ret = 0;
        }
        else if (argc > 4)
        {
            for(i = 2; i < (argc - 1); i++)
            {

                Shape *t;
                if (vn[1] == INT32_MAX)
                {
                    t = new Triangle(this->vertices(v[1]),
                                     this->vertices(v[i]),
                                     this->vertices(v[i + 1]));
                }
                else
                {
                    t = new SmoothTriangle(this->vertices(v[1]),
                                           this->vertices(v[i]),
                                           this->vertices(v[i + 1]),
                                           this->verticesNormal(vn[1]),
                                           this->verticesNormal(vn[i]),
                                           this->verticesNormal(vn[i + 1]));
                }
                this->currentGroup->addObject(t);
            }
            ret = 0;
        }
        else
        {
            printf("ERROR: Malformed file at line %d: Too few/many parameters!\n", currentLine);
        }
    }
    else if (strncmp(argv[0], "g", 2) == 0)
    {
        if (argc == 2)
        {
            this->addGroup(new Group(argv[1]));
        }
        else
        {
            printf("ERROR: Malformed file at line %d: Too few/many parameters!\n", currentLine);
        }
    }
    return ret;
}

void OBJFile::lock()
{
    Shape::lock();

    this->baseGroup->lock();
}