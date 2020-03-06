/*
 *  DoRayMe - a quick and dirty Raytracer
 *  OBJ File header
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#ifndef DORAYME_OBJFILE_H
#define DORAYME_OBJFILE_H

#include <shape.h>
#include <renderstat.h>

class OBJFile : public Shape
{
private:
    uint32_t allocatedFaceGroupCount;
    Shape* *faceGroupList;
    uint32_t faceGroupCount;

    uint32_t allocatedVertexCount;
    Tuple* *vertexList;
    uint32_t vertexCount;


private:
    Intersect localIntersect(Ray r);
    Tuple localNormalAt(Tuple point);

public:
    /* Some stats */
    uint32_t ignoredLines;

protected:
    void addGroup(Shape *group);
    void addVertex(Tuple *vertex);

    void parseLine(char *line);
    int execLine(int argc, char *argv[]);
    BoundingBox bounds;

public:
    OBJFile();
    OBJFile(const char *filepath);

    int parseOBJFile(const char *content);


    Intersect intersect(Ray r);
    BoundingBox getLocalBounds();
    BoundingBox getBounds();

    void updateBoundingBox();
    void updateTransform();

    void dumpMe(FILE * fp);
};

#endif /* DORAYME_OBJFILE_H */
