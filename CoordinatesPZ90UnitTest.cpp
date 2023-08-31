//
// Created by paul on 8/31/23.
//

#include <gtest/gtest.h>

#include "CoordinatesPZ90.h"

auto * testObject = new CoordinatesPZ90;

TEST(SetCoordinatesTests, Equivalence){
    testObject->setGeodeticCoordinates(42 * M_PI / 180, 32 * M_PI / 180);
    EXPECT_EQ(42 * M_PI / 180, testObject->getGeodeticLatitudeB());
    testObject->setRectangularCoordinates(100000, 100000);
    EXPECT_EQ(100000, testObject->getRectangularX());
}

TEST(GeodeticToRectangularTransition, EachSideEquivalence){
    double latitudeBefore, latitudeAfter, longitudeBefore, longitudeAfter;
    double rectXBefore, rectXAfter, rectYBefore, rectYAfter;
    testObject->setGeodeticCoordinates(42 * M_PI / 180, 32 * M_PI / 180);
    latitudeBefore = testObject->getGeodeticLatitudeB();
    longitudeBefore = testObject->getGeodeticLongitudeL();
    testObject->geodeticToRectangular();
    rectXBefore = testObject->getRectangularX();
    rectYBefore = testObject->getRectangularY();
    testObject->rectangularToGeodetic();
    latitudeAfter = testObject->getGeodeticLatitudeB();
    longitudeAfter = testObject->getGeodeticLongitudeL();
    EXPECT_EQ(latitudeBefore, latitudeAfter);
    EXPECT_EQ(longitudeBefore, longitudeAfter);
}