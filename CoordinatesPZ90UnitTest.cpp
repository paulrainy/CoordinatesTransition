//
// Created by paul on 8/31/23.
//

#include <gtest/gtest.h>
#include <iostream>

#include "CoordinatesPZ90.h"

auto * testObject = new CoordinatesPZ90;

TEST(SetCoordinatesTests, Equivalence){ //тест сеттеров с геттерами
    testObject->setGeodeticCoordinates(42 * M_PI / 180, 32 * M_PI / 180);
    EXPECT_EQ(42 * M_PI / 180, testObject->getGeodeticLatitudeB());
    EXPECT_EQ(32, testObject->getGeodeticLongitudeL());

    testObject->setRectangularCoordinates(100000, 100000);
    EXPECT_EQ(100000, testObject->getRectangularX());
    EXPECT_EQ(100000, testObject->getRectangularY());
}

TEST(GeodeticToRectangularTransitionTest, EachSideEquivalence){ //тест перевода систем координат
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
    //погрешность соответствует требованию в 10^-6

    testObject->geodeticToRectangular();//второй проход

    rectXAfter = testObject->getRectangularX();
    rectYAfter = testObject->getRectangularY();

    EXPECT_EQ(round(rectXBefore * 10000) / 10000, round(rectXAfter * 10000) / 10000);
    EXPECT_EQ(round(rectYBefore * 1000) / 1000, round(rectYAfter * 1000) / 1000);
    //погрешность не соответствует требованию ни в одном из случаев
}

TEST(sinHelpBTest, Equivalence){ //тест вспомогательного метода по возведению синуса в требуемую степень
    testObject->setGeodeticCoordinates(42 * M_PI / 180, 32 * M_PI / 180);
    EXPECT_EQ(pow(sin(42 * M_PI / 180), 2), testObject->sinHelpB(2));
}

TEST(powHelpL2Test, Equivalence){ //тест вспомогательного метода
    testObject->setGeodeticCoordinates(42 * M_PI / 180, 32 * M_PI / 180);
    testObject->geodeticToRectangular();
    EXPECT_EQ(pow(((testObject->getGeodeticLongitudeL() - (3.0 + 6.0 * (static_cast<int>((6.0 +
        testObject->getGeodeticLongitudeL()) / 6.0) - 1.0))) / 57.29577951), 2), testObject->powHelpL2());
}

TEST(loadAndGetFromVectorTest, Equivalence){
    testObject->setGeodeticCoordinates(42 * M_PI / 180, 32 * M_PI / 180); //создание геодезической координаты
    testObject->loadGeodeticToVector(); //загрузка координаты в вектор
    testObject->setGeodeticCoordinates(52 * M_PI / 180, 42 * M_PI / 180); //вторая координата
    testObject->loadGeodeticToVector(); //загрузка в вектор

    testObject->setRectangularCoordinates(100000, 200000); //создание прямоугольной координаты
    testObject->loadRectangularToVector(); //загрузка в вектор
    testObject->setRectangularCoordinates(3000000, 4000000); //вторая координата
    testObject->loadRectangularToVector(); //загрузка

    testObject->getMemberFromGeodeticVector(0); //возвращаем из вектора первую записанную координату
    EXPECT_EQ(42 * M_PI / 180, testObject->getGeodeticLatitudeB()); //проверка на соответствие широты
    EXPECT_EQ(32, testObject->getGeodeticLongitudeL()); //проверка на соответствие долготы

    testObject->getMemberFromGeodeticVector(1); //возвращаем из вектора вторую координату
    EXPECT_EQ(52 * M_PI / 180, testObject->getGeodeticLatitudeB()); //то же самое как и выше
    EXPECT_EQ(42, testObject->getGeodeticLongitudeL());

    testObject->getMemberFromRectangularVector(0);
    EXPECT_EQ(100000, testObject->getRectangularX());
    EXPECT_EQ(200000, testObject->getRectangularY());

    testObject->getMemberFromRectangularVector(1);
    EXPECT_EQ(3000000, testObject->getRectangularX());
    EXPECT_EQ(4000000, testObject->getRectangularY());
}


