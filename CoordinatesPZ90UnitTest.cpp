//
// Created by paul on 8/31/23.
//

#include <gtest/gtest.h>

#include "CoordinatesPZ90.h"

auto * testObject = new CoordinatesPZ90;

//тест сеттеров с геттерами
TEST(SetCoordinatesTests, Equivalence){
    testObject->setGeodeticCoordinates(42 * M_PI / 180, 32 * M_PI / 180);
    EXPECT_EQ(42 * M_PI / 180, testObject->getGeodeticLatitudeB());
    EXPECT_EQ(32, testObject->getGeodeticLongitudeL());

    testObject->setRectangularCoordinates(100000, 100000);
    EXPECT_EQ(100000, testObject->getRectangularX());
    EXPECT_EQ(100000, testObject->getRectangularY());
}

//тест перевода систем координат
TEST(GeodeticToRectangularTransitionTest, EachSideEquivalence){
    double latitudeBefore, latitudeAfter, longitudeBefore, longitudeAfter;
    double rectXBefore, rectXAfter, rectYBefore, rectYAfter;

    testObject->setGeodeticCoordinates(42 * M_PI / 180, 32 * M_PI / 180);
    latitudeBefore = testObject->getGeodeticLatitudeB();
    longitudeBefore = testObject->getGeodeticLongitudeL();

    testObject->geodeticToRectangular();//первый проход

    rectXBefore = testObject->getRectangularX();
    rectYBefore = testObject->getRectangularY();

    testObject->rectangularToGeodetic();//первый обратный проход

    latitudeAfter = testObject->getGeodeticLatitudeB();
    longitudeAfter = testObject->getGeodeticLongitudeL();

    EXPECT_EQ(round(latitudeBefore * 1000000) / 1000000, round(latitudeAfter * 1000000) / 1000000);
    EXPECT_EQ(round(longitudeBefore * 1000000) / 1000000, round(longitudeAfter * 1000000) / 1000000);
    //погрешность соответсвует требованию в 10^-6

    testObject->geodeticToRectangular();//второй проход

    rectXAfter = testObject->getRectangularX();
    rectYAfter = testObject->getRectangularY();

    EXPECT_EQ(round(rectXBefore * 10000) / 10000, round(rectXAfter * 10000) / 10000);
    EXPECT_EQ(round(rectYBefore * 1000) / 1000, round(rectYAfter * 1000) / 1000);
    //погрешность не соответствует требованию ни в одном из случаев
}

