//
// Created by paul on 8/31/23.
//

#include <gtest/gtest.h>
#include <iostream>

#include "CoordinatesSK42.h"

auto * testObjectSK42 = new CoordinatesSK42;

TEST(SetRectangularCoordinatesTest, Equivalence){
    testObjectSK42->setRectangularCoordinates(1000, 2000);
    EXPECT_EQ(1000, testObjectSK42->getRectangularX());
    EXPECT_EQ(2000, testObjectSK42->getRectangularY());
}

TEST(loadAndGetFromRectVectorTest, Equivalence){
    EXPECT_TRUE(testObjectSK42->vectorRectangularXSK42->empty()); //проверка на отсутствие элементов в векторе
    EXPECT_TRUE(testObjectSK42->vectorRectangularYSK42->empty());

    testObjectSK42->setRectangularCoordinates(1000000, 2000000);
    testObjectSK42->loadRectangularToVector();
    testObjectSK42->setRectangularCoordinates(3000, 4000);
    testObjectSK42->loadRectangularToVector();

    EXPECT_FALSE(testObjectSK42->vectorRectangularXSK42->empty()); //проверка на наличие элементов в векторе
    EXPECT_FALSE(testObjectSK42->vectorRectangularYSK42->empty());

    testObjectSK42->getMemberFromRectangularVector(0);

    EXPECT_EQ(1000000, testObjectSK42->getRectangularX());
    EXPECT_EQ(2000000, testObjectSK42->getRectangularY());

    testObjectSK42->getMemberFromRectangularVector(1);

    EXPECT_EQ(3000, testObjectSK42->getRectangularX());
    EXPECT_EQ(4000, testObjectSK42->getRectangularY());

}