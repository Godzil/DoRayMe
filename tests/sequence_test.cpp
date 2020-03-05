/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Sequence unit tests
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <sequence.h>
#include <gtest/gtest.h>

TEST(SequenceTest, A_number_generator_returns_a_cyclic_sequence_of_numbers)
{
    double seqList[] = { 0.1, 0.5, 1.0};
    Sequence gen = Sequence(seqList, 3);

    ASSERT_EQ(gen.next(), 0.1);
    ASSERT_EQ(gen.next(), 0.5);
    ASSERT_EQ(gen.next(), 1.0);
    ASSERT_EQ(gen.next(), 0.1);
}