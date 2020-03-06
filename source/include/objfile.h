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

#include <stdint.h>
#include <tuple.h>
#include <shape.h>
#include <group.h>
#include <renderstat.h>

class OBJFile : public Shape
{
private:
    uint32_t allocatedFaceGroupCount;
    Group* *faceGroupList;
    uint32_t faceGroupCount;

    uint32_t allocatedVertexCount;
    Point* *vertexList;
    uint32_t vertexCount;

    uint32_t allocatedVertexNormalCount;
    Vector* *vertexNormalList;
    uint32_t vertexNormalCount;

private:
    Intersect localIntersect(Ray r);
    Tuple localNormalAt(Tuple point, Intersection *hit = nullptr);

public:
    /* Some stats */
    uint32_t ignoredLines;

protected:
    void addGroup(Group *group);
    void addVertex(Point *vertex);
    void addVertexNormal(Vector *vertexNormal);

    void parseLine(char *line, uint32_t currentLine);
    int execLine(int argc, char *argv[], uint32_t currentLine);
    BoundingBox bounds;

public:
    OBJFile();
    OBJFile(const char *filepath);

    int parseOBJFile(const char *content);

    /* OBJ file expect the first vertice to be 1 and not 0 */
    Point vertices(uint32_t i) { return *this->vertexList[i - 1]; };
    Vector verticesNormal(uint32_t i) { return *this->vertexNormalList[i - 1]; };
    Group *groups(uint32_t i) { return this->faceGroupList[i];  };
    Intersect intersect(Ray r);
    BoundingBox getLocalBounds();
    BoundingBox getBounds();

    bool includes(Shape *b);

    void updateBoundingBox();
    void updateTransform();

    void dumpMe(FILE * fp);
};

#endif /* DORAYME_OBJFILE_H */
