//
// Created by paul on 3/13/24.
//

#include "CoordinatesWGS84.h"

TEST(setGeodeticCoordinatesTestWGS84, Equivalence){
    auto * testObjectWGS84 = new CoordinatesWGS84;
    testObjectWGS84->setGeodeticCoordinates(30 * M_PI / 180, 20 * M_PI / 180);
    EXPECT_EQ(30 * M_PI / 180, testObjectWGS84->getGeodeticLatitudeB());
    EXPECT_EQ(20 * M_PI / 180, testObjectWGS84->getGeodeticLongitudeL());
}
