/*
 *  DoRayMe - a quick and dirty Raytracer
 *  OBJ File unit tests
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <objfile.h>
#include <math.h>
#include <gtest/gtest.h>
#include <triangle.h>

TEST(OBJFileTest, Ignoring_unrecognised_lines)
{
    const char gibberish[] = "There was a young lady named Bright\n"
                             "who traveled much faster than light\n"
                             "She set out one day\n"
                             "in a relative way\n"
                             "and came back the previous night.\n";

    OBJFile parser = OBJFile();
    parser.parseOBJFile(gibberish);

    ASSERT_EQ(parser.ignoredLines, 5);
}

TEST(OBJFileTest, Vertex_record)
{
    const char file[] = "v -1 1 0\n"
                        "v -1.0000 0.5000 0.0000\n"
                        "v 1 0 0\n"
                        "v 1 1 0\n";

    OBJFile parser = OBJFile();
    parser.parseOBJFile(file);

    ASSERT_EQ(parser.vertices(1), Point(-1, 1, 0));
    ASSERT_EQ(parser.vertices(2), Point(-1, 0.5, 0));
    ASSERT_EQ(parser.vertices(3), Point(1, 0, 0));
    ASSERT_EQ(parser.vertices(4), Point(1, 1, 0));
}

TEST(OBJFileTest, Parsing_triangle_faces)
{
    const char file[] = "v -1 1 0\n"
                        "v -1 0 0\n"
                        "v 1 0 0\n"
                        "v 1 1 0\n"
                        "\n"
                        "f 1 2 3\n"
                        "f 1 3 4\n";

    OBJFile parser = OBJFile();
    parser.parseOBJFile(file);

    Group *g0 = parser.groups(0);

    Triangle *t1 = (Triangle *)(*g0)[0];
    Triangle *t2 = (Triangle *)(*g0)[1];

    ASSERT_EQ(t1->p1, parser.vertices(1));
    ASSERT_EQ(t1->p2, parser.vertices(2));
    ASSERT_EQ(t1->p3, parser.vertices(3));

    ASSERT_EQ(t2->p1, parser.vertices(1));
    ASSERT_EQ(t2->p2, parser.vertices(3));
    ASSERT_EQ(t2->p3, parser.vertices(4));
}

TEST(OBJFileTest, Triangulating_polygons)
{
    const char file[] = "v -1 1 0\n"
                        "v -1 0 0\n"
                        "v 1 0 0\n"
                        "v 1 1 0\n"
                        "v 0 2 0\n"
                        "\n"
                        "f 1 2 3 4 5\n";

    OBJFile parser = OBJFile();
    parser.parseOBJFile(file);

    Group *g0 = parser.groups(0);

    Triangle *t1 = (Triangle *)(*g0)[0];
    Triangle *t2 = (Triangle *)(*g0)[1];
    Triangle *t3 = (Triangle *)(*g0)[2];

    ASSERT_EQ(t1->p1, parser.vertices(1));
    ASSERT_EQ(t1->p2, parser.vertices(2));
    ASSERT_EQ(t1->p3, parser.vertices(3));

    ASSERT_EQ(t2->p1, parser.vertices(1));
    ASSERT_EQ(t2->p2, parser.vertices(3));
    ASSERT_EQ(t2->p3, parser.vertices(4));

    ASSERT_EQ(t3->p1, parser.vertices(1));
    ASSERT_EQ(t3->p2, parser.vertices(4));
    ASSERT_EQ(t3->p3, parser.vertices(5));
}

TEST(OBJFileTest, Triangle_in_groups)
{
    OBJFile parser = OBJFile("triangles.obj");

    /* TODO: Add group name search/test */
    Group *g1 = parser.groups(1);
    Group *g2 = parser.groups(2);

    Triangle *t1 = (Triangle *)(*g1)[0];
    Triangle *t2 = (Triangle *)(*g2)[0];

    ASSERT_EQ(t1->p1, parser.vertices(1));
    ASSERT_EQ(t1->p2, parser.vertices(2));
    ASSERT_EQ(t1->p3, parser.vertices(3));

    ASSERT_EQ(t2->p1, parser.vertices(1));
    ASSERT_EQ(t2->p2, parser.vertices(3));
    ASSERT_EQ(t2->p3, parser.vertices(4));
}