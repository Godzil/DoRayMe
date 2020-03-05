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

TEST(OBJFileTest, Ignoring_unrecognised_lines)
{
    const char gibberish[] = "There was a young lane named Bright\n"
                             "who traveled much faster than light\n"
                             "She set out one day\n"
                             "in a relative way\n"
                             "and came back the previous night.\n";

    OBJFile parser = OBJFile();
    parser.parseOBJFile(gibberish);

    ASSERT_EQ(parser.ignoredLines, 5);
}