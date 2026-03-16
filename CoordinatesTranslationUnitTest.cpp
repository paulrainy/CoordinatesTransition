//
// Created by paul on 29.11.23.
//

#include "CoordinatesTranslation.h"

auto * testObject = new CoordinatesTranslation;

TEST(setCoordinateObjectPZ90Test, Equivalence){
    testObject->setCoordinateObjectPZ90(1000, 2000, false);
    EXPECT_EQ(1000, testObject->getCoordinateObjectPZ90().getRectangularX());
    EXPECT_EQ(2000, testObject->getCoordinateObjectPZ90().getRectangularY());
    testObject->setCoordinateObjectPZ90(30 * M_PI / 180, 40 * M_PI / 180, true);
    EXPECT_EQ(30 * M_PI / 180, testObject->getCoordinateObjectPZ90().getGeodeticLatitudeB());
    EXPECT_EQ(40 * M_PI / 180, testObject->getCoordinateObjectPZ90().getGeodeticLongitudeL());
}

TEST(setCoordinateObjectSK42Test, Equivalence){
    testObject->setCoordinateObjectSK42(1000, 2000);
    EXPECT_EQ(1000, testObject->getCoordinateObjectSK42().getRectangularX());
    EXPECT_EQ(2000, testObject->getCoordinateObjectSK42().getRectangularY());
}

TEST(setCoordinateObjectWGS84Test, Equivalence){
    testObject->setCoordinateObjectWGS84(10 * M_PI / 180, 20 * M_PI / 180);
    EXPECT_EQ(10 * M_PI / 180, testObject->getCoordinateObjectWGS84().getGeodeticLatitudeB());
    EXPECT_EQ(20 * M_PI / 180, testObject->getCoordinateObjectWGS84().getGeodeticLongitudeL());
}

TEST(PZ90toSK42Test, Equivalence){
    testObject->setCoordinateObjectPZ90(30 * M_PI / 180, 40 * M_PI / 180, true);
    testObject->PZ90toSK42();
    std::cout<< testObject->getCoordinateObjectSK42().getRectangularX() << std::endl;
    std::cout << testObject->getCoordinateObjectSK42().getRectangularY() << std::endl;
    EXPECT_EQ(3320593, round(testObject->getCoordinateObjectSK42().getRectangularX()));
    EXPECT_EQ(7596490, round(testObject->getCoordinateObjectSK42().getRectangularY()));
}

TEST(SK42toPZ90Test, Equivalence){
    testObject->setCoordinateObjectSK42(3400000, 7600000);
    testObject->SK42toPZ90();
    std::cout << testObject->getCoordinateObjectPZ90().getGeodeticLatitudeB() << std::endl;
    std::cout << testObject->getCoordinateObjectPZ90().getGeodeticLongitudeL() << std::endl;
    EXPECT_EQ(0.536, round(testObject->getCoordinateObjectPZ90().getGeodeticLatitudeB() * 1000) / 1000);
    EXPECT_EQ(0.699, round(testObject->getCoordinateObjectPZ90().getGeodeticLongitudeL() * 1000) / 1000);
}

TEST(PZ90toWGS84Test, Equivalence){
    testObject->setCoordinateObjectPZ90(40 * M_PI / 180, 40 * M_PI / 180, true);
    testObject->PZ90toWGS84();
    std::cout << testObject->getCoordinateObjectWGS84().getGeodeticLatitudeB() * 180 / M_PI << std::endl;
    std::cout << testObject->getCoordinateObjectWGS84().getGeodeticLongitudeL() * 180 / M_PI << std::endl;
    EXPECT_LT(40 * 100000, testObject->getCoordinateObjectWGS84().getGeodeticLatitudeB() * 180 / M_PI * 100000);
    EXPECT_LT(40 * 100000, testObject->getCoordinateObjectWGS84().getGeodeticLongitudeL() * 180 / M_PI * 100000);
}

//TEST(WGS84toPZ90Test, Equivalence){
//    testObject->setCoordinateObjectWGS84(30 * M_PI / 180, 40 * M_PI / 180);
//    testObject->WGS84toPZ90();
//    std::cout << testObject->getCoordinateObjectPZ90().getGeodeticLatitudeB() << std::endl;
//    std::cout << testObject->getCoordinateObjectPZ90().getGeodeticLongitudeL() << std::endl;
//    EXPECT_EQ(30 * M_PI / 180 + 0.00036, testObject->getCoordinateObjectPZ90().getGeodeticLatitudeB());
//    EXPECT_EQ(40 * M_PI / 180 - 0.00018, testObject->getCoordinateObjectPZ90().getGeodeticLongitudeL());
//}