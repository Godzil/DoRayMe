/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Pattern unit tests
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */

#include <pattern.h>
#include <strippattern.h>
#include <gradientpattern.h>
#include <ringpattern.h>
#include <checkerspattern.h>
#include <testpattern.h>
#include <transformation.h>
#include <colour.h>
#include <sphere.h>
#include <gtest/gtest.h>
#include <material.h>
#include <uv_pattern.h>
#include <uv_checkers.h>
#include <texturemap.h>

#ifdef ENABLE_LUA_SUPPORT
extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}
#include <luapattern.h>
#endif

Colour black = Colour(0, 0, 0);
Colour white = Colour(1, 1, 1);

TEST(PatternTest, Creating_a_stripe_pattern)
{
    StripPattern p = StripPattern(white, black);

    ASSERT_EQ(p.a, white);
    ASSERT_EQ(p.b, black);
}

TEST(PatternTest, A_strip_pattern_is_constant_in_y)
{
    StripPattern p = StripPattern(white, black);

    ASSERT_EQ(p.patternAt(Point(0, 0, 0)), white);
    ASSERT_EQ(p.patternAt(Point(0, 1, 0)), white);
    ASSERT_EQ(p.patternAt(Point(0, 2, 0)), white);
}

TEST(PatternTest, A_strip_pattern_is_constant_in_z)
{
    StripPattern p = StripPattern(white, black);

    ASSERT_EQ(p.patternAt(Point(0, 0, 0)), white);
    ASSERT_EQ(p.patternAt(Point(0, 0, 1)), white);
    ASSERT_EQ(p.patternAt(Point(0, 0, 2)), white);
}

TEST(PatternTest, A_strip_pattern_alternate_in_x)
{
    StripPattern p = StripPattern(white, black);

    ASSERT_EQ(p.patternAt(Point(0, 0, 0)), white);
    ASSERT_EQ(p.patternAt(Point(0.9, 0, 0)), white);
    ASSERT_EQ(p.patternAt(Point(1, 0, 0)), black);
    ASSERT_EQ(p.patternAt(Point(-0.1, 0, 0)), black);
    ASSERT_EQ(p.patternAt(Point(-1, 0, 0)), black);
    ASSERT_EQ(p.patternAt(Point(-1.1, 0, 0)), white);
}

TEST(PatternTest, Lightning_with_a_pattern_applied)
{
    Sphere s = Sphere();
    Material m;
    StripPattern p = StripPattern(white, black);
    m.pattern = &p;
    m.ambient = 1;
    m.diffuse = 0;
    m.specular = 0;

    Tuple eyev = Vector(0, 0, -1);
    Tuple normalv = Vector(0, 0, -1);
    Light light = Light(POINT_LIGHT, Point(0, 0, -10), Colour(1, 1, 1));

    Colour c1 = m.lighting(light, Point(0, 9, 0), eyev, normalv, &s, false);
    Colour c2 = m.lighting(light, Point(1, 1, 0), eyev, normalv, &s, false);

    ASSERT_EQ(c1, Colour(1, 1, 1));
    ASSERT_EQ(c2, Colour(0, 0, 0));
}

TEST(PatternTest, Stripe_with_an_object_transformation)
{
    Sphere s = Sphere();
    s.setTransform(scaling(2, 2, 2));
    StripPattern pattern = StripPattern(white, black);
    Colour c = pattern.patternAtObject(&s, Point(1.5, 0, 0));

    ASSERT_EQ(c, white);
}

TEST(PatternTest, Stripe_with_a_pattern_transformation)
{
    Sphere s = Sphere();
    StripPattern pattern = StripPattern(white, black);
    pattern.setTransform(scaling(2, 2, 2));
    Colour c = pattern.patternAtObject(&s, Point(1.5, 0, 0));

    ASSERT_EQ(c, white);
}

TEST(PatternTest, Stripe_with_both_an_object_and_a_pattern_transformation)
{
    Sphere s = Sphere();
    s.setTransform(scaling(2, 2, 2));
    StripPattern pattern = StripPattern(white, black);
    pattern.setTransform(translation(0.5, 0, 0));

    Colour c = pattern.patternAtObject(&s, Point(2.5, 0, 0));

    ASSERT_EQ(c, white);
}

TEST(PatternTest, The_default_pattern_transformation)
{
    TestPattern pattern = TestPattern();

    ASSERT_EQ(pattern.transformMatrix, Matrix4().identity());
}

TEST(PatternTest, Assigning_a_transformation)
{
    TestPattern pattern = TestPattern();
    pattern.setTransform(translation(1, 2, 3));

    ASSERT_EQ(pattern.transformMatrix, translation(1, 2, 3));
}

TEST(PatternTest, A_pattern_with_an_object_transformation)
{
    Sphere s = Sphere();
    s.setTransform(scaling(2, 2, 2));
    TestPattern pattern = TestPattern();

    Colour c = pattern.patternAtObject(&s, Point(2, 3, 4));

    ASSERT_EQ(c, Colour(1, 1.5, 2));
}

TEST(PatternTest, A_pattern_with_a_pattern_transformation)
{
    Sphere s = Sphere();
    TestPattern pattern = TestPattern();
    pattern.setTransform(scaling(2, 2, 2));

    Colour c = pattern.patternAtObject(&s, Point(2, 3, 4));

    ASSERT_EQ(c, Colour(1, 1.5, 2));
}

TEST(PatternTest, A_pattern_with_an_object_and_a_pattern_transformation)
{
    Sphere s = Sphere();
    s.setTransform(scaling(2, 2, 2));
    TestPattern pattern = TestPattern();
    pattern.setTransform(translation(0.5, 1, 1.5));

    Colour c = pattern.patternAtObject(&s, Point(2.5, 3, 3.5));

    ASSERT_EQ(c, Colour(0.75, 0.5, 0.25));
}

TEST(PatternTest, A_gradient_linearly_interpolates_betweens_colors)
{
    GradientPattern pattern = GradientPattern(white, black);

    ASSERT_EQ(pattern.patternAt(Point(0.25, 0, 0)), Colour(0.75, 0.75, 0.75));
    ASSERT_EQ(pattern.patternAt(Point(0.5, 0, 0)), Colour(0.5, 0.5, 0.5));
    ASSERT_EQ(pattern.patternAt(Point(0.75, 0, 0)), Colour(0.25, 0.25, 0.25));
}

TEST(PatternTest, A_ring_should_extend_in_both_x_and_z)
{
    RingPattern pattern = RingPattern(white, black);

    ASSERT_EQ(pattern.patternAt(Point(0, 0, 0)), white);
    ASSERT_EQ(pattern.patternAt(Point(1, 0, 0)), black);
    ASSERT_EQ(pattern.patternAt(Point(0, 0, 1)), black);

    /* 0.708 is just bit more than sqrt(2)/2 */
    ASSERT_EQ(pattern.patternAt(Point(0.708, 0, 0.708)), black);
}

TEST(PatternTest, Checkers_should_repeat_in_x)
{
    CheckersPattern pattern = CheckersPattern(white, black);

    ASSERT_EQ(pattern.patternAt(Point(0, 0, 0)), white);
    ASSERT_EQ(pattern.patternAt(Point(0.99, 0, 0)), white);
    ASSERT_EQ(pattern.patternAt(Point(1.01, 0, 0)), black);
}

TEST(PatternTest, Checkers_should_repeat_in_y)
{
    CheckersPattern pattern = CheckersPattern(white, black);

    ASSERT_EQ(pattern.patternAt(Point(0, 0, 0)), white);
    ASSERT_EQ(pattern.patternAt(Point(0, 0.99, 0)), white);
    ASSERT_EQ(pattern.patternAt(Point(0, 1.01, 0)), black);
}

TEST(PatternTest, Checkers_should_repeat_in_z)
{
    CheckersPattern pattern = CheckersPattern(white, black);

    ASSERT_EQ(pattern.patternAt(Point(0, 0, 0)), white);
    ASSERT_EQ(pattern.patternAt(Point(0, 0, 0.99)), white);
    ASSERT_EQ(pattern.patternAt(Point(0, 0, 1.01)), black);
}

#ifdef ENABLE_LUA_SUPPORT
TEST(PatternTest, Simple_test_of_a_lua_pattern)
{
    int error;
    LuaPattern pattern = LuaPattern(white, black);
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    pattern.setLua(L);

    pattern.setLuaFunctionName("pat");

    error = luaL_loadstring(L, "function pat(x, y, z, a, b)\n"
                               "    local v = math.floor(x) + math.floor(y) + math.floor(z)\n"
                               "    if (v % 2) == 0 then\n"
                               "        return a.r, a.g, a.b\n"
                               "    end\n"
                               "    return b.r, b.g, b.b\n"
                               "end");

    if (error)
    {
        fprintf(stderr, "%s\n", lua_tostring(L, -1));
        lua_pop(L, 1);  /* pop error message from the stack */
    }
    ASSERT_EQ(error, 0);

    error = lua_pcall(L, 0, 0, 0);
    if (error)
    {
        fprintf(stderr, "%s\n", lua_tostring(L, -1));
        lua_pop(L, 1);  /* pop error message from the stack */
    }
    ASSERT_EQ(error, 0);

    ASSERT_EQ(pattern.patternAt(Point(0, 0, 0)), white);
    ASSERT_EQ(pattern.patternAt(Point(0, 0.99, 0)), white);
    ASSERT_EQ(pattern.patternAt(Point(0, 1.01, 0)), black);

    lua_close(L);
}
#endif

TEST(PatternTest, Checkers_pattern_in_2D)
{
    UVCheckers checkers = UVCheckers(2, 2, black, white);

    ASSERT_EQ(checkers.uvPatternAt(0.0, 0.0), black);
    ASSERT_EQ(checkers.uvPatternAt(0.5, 0.0), white);
    ASSERT_EQ(checkers.uvPatternAt(0.0, 0.5), white);
    ASSERT_EQ(checkers.uvPatternAt(0.5, 0.5), black);
    ASSERT_EQ(checkers.uvPatternAt(1.0, 1.0), black);
}

TEST(PatternTest, Using_a_spherical_mapping_on_a_3d_point)
{
    Point testList[] = {
            Point( 0,  0, -1),
            Point( 1,  0,  0),
            Point( 0,  0,  1),
            Point(-1,  0,  0),
            Point( 0,  1,  0),
            Point( 0, -1,  0),
            Point(sqrt(2)/2, sqrt(2)/2, 0),
    };

    double testResults[][2] {
            {0.0,  0.5},
            {0.25, 0.5},
            {0.5,  0.5},
            {0.75, 0.5},
            {0.5,  1.0},
            {0.5,  0.0},
            {0.25, 0.75},
    };

    int testCount = sizeof(testList)/sizeof((testList)[0]);
    int i;

    TextureMap tm = TextureMap(SPHERICAL_MAP, nullptr);

    for(i = 0; i < testCount; i++)
    {
        double u, v;
        tm.sphericalMap(testList[i], u, v);
        ASSERT_TRUE(double_equal(u, testResults[i][0]));
        ASSERT_TRUE(double_equal(v, testResults[i][1]));
    }
}

TEST(PatternTest, Using_a_texture_map_with_a_spherical_map)
{
    Point testList[] = {
            Point(  0.4315,  0.4670,  0.7719),
            Point( -0.9654,  0.2252, -0.0534),
            Point(  0.1039,  0.7090,  0.6975),
            Point( -0.4986, -0.7856, -0.3663),
            Point( -0.0317, -0.9395,  0.3411),
            Point(  0.4809, -0.7721,  0.4154),
            Point(  0.0285, -0.9612, -0.2745),
            Point( -0.5734, -0.2162, -0.7903),
            Point(  0.7688, -0.1470,  0.6223),
            Point( -0.7652,  0.2175,  0.6060),
    };

    Colour testResults[] {
            white,
            black,
            white,
            black,
            black,
            black,
            black,
            white,
            black,
            black,
    };

    int testCount = sizeof(testList)/sizeof((testList)[0]);
    int i;

    UVCheckers uvpat = UVCheckers(16, 8, black, white);
    TextureMap tm = TextureMap(SPHERICAL_MAP, &uvpat);

    for(i = 0; i < testCount; i++)
    {
        Colour ret = tm.patternAt(testList[i]);
        EXPECT_EQ(ret, testResults[i]);
    }
}