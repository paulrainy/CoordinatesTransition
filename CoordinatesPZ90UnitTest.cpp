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
    //вспомогательные переменные
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

TEST(loadAndGetFromVectorTest, Equivalence){ //тест загрузки и выгрузки из вектора
    testObject->setGeodeticCoordinates(42 * M_PI / 180, 32 * M_PI / 180); //создание геодезической координаты
    testObject->loadGeodeticToVector(); //загрузка координаты в вектор
    testObject->setGeodeticCoordinates(52 * M_PI / 180, 42 * M_PI / 180); //вторая координата
    testObject->loadGeodeticToVector(); //загрузка в вектор

    EXPECT_FALSE(testObject->vectorGeodeticLatitudePZ90->empty()); //проверка на наличие элементов в векторе
    EXPECT_FALSE(testObject->vectorGeodeticLongitudePZ90->empty());

    testObject->setRectangularCoordinates(100000, 200000); //создание прямоугольной координаты
    testObject->loadRectangularToVector(); //загрузка в вектор
    testObject->setRectangularCoordinates(3000000, 4000000); //вторая координата
    testObject->loadRectangularToVector(); //загрузка

    EXPECT_FALSE(testObject->vectorRectangularXPZ90->empty()); //проверка на наличие элементов в векторе
    EXPECT_FALSE(testObject->vectorRectangularYPZ90->empty());

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

    testObject->vectorGeodeticLatitudePZ90->clear(); //очистка векторов для последующих тестов
    testObject->vectorGeodeticLongitudePZ90->clear();
    testObject->vectorRectangularXPZ90->clear();
    testObject->vectorRectangularYPZ90->clear();
}

TEST(geodeticToRectangularVectorTransitionTest, EachSideEquivalence){
    //вспомогательные переменные
    double latitudeBeforeFirst, latitudeAfterFirst, longitudeBeforeFirst, longitudeAfterFirst;
    double latitudeBeforeSecond, latitudeAfterSecond, longitudeBeforeSecond, longitudeAfterSecond;
    double latitudeBeforeThird, latitudeAfterThird, longitudeBeforeThird, longitudeAfterThird;
    double rectXBeforeFirst, rectXAfterFirst, rectYBeforeFirst, rectYAfterFirst;
    double rectXBeforeSecond, rectXAfterSecond, rectYBeforeSecond, rectYAfterSecond;
    double rectXBeforeThird, rectXAfterThird, rectYBeforeThird, rectYAfterThird;

    testObject->setGeodeticCoordinates(42 * M_PI / 180, 32 * M_PI / 180); //создание геодезической координаты
    latitudeBeforeFirst = testObject->getGeodeticLatitudeB(); //запись во вспомогательную переменную
    std::cout << latitudeBeforeFirst << std::endl; //вывод для визуального удобства
    longitudeBeforeFirst = testObject->getGeodeticLongitudeL();
    std::cout << longitudeBeforeFirst << std::endl;
    testObject->loadGeodeticToVector(); //загрузка координаты в вектор

    testObject->setGeodeticCoordinates(52 * M_PI / 180, 42 * M_PI / 180); //вторая координата
    latitudeBeforeSecond = testObject->getGeodeticLatitudeB();
    std::cout << latitudeBeforeSecond << std::endl;
    longitudeBeforeSecond = testObject->getGeodeticLongitudeL();
    std::cout << longitudeBeforeSecond << std::endl;
    testObject->loadGeodeticToVector();

    testObject->setGeodeticCoordinates(62 * M_PI / 180, 52 * M_PI / 180); //третья координата
    latitudeBeforeThird = testObject->getGeodeticLatitudeB();
    std::cout << latitudeBeforeThird << std::endl;
    longitudeBeforeThird = testObject->getGeodeticLongitudeL();
    std::cout << longitudeBeforeThird << std:: endl;
    std::cout << std::endl;

    testObject->loadGeodeticToVector();

    EXPECT_FALSE(testObject->vectorGeodeticLatitudePZ90->empty()); //проверка на наличие элементов в векторе
    EXPECT_FALSE(testObject->vectorGeodeticLongitudePZ90->empty());

    testObject->fromGeodeticToRectangularVector(); //перевод группы координат

    EXPECT_EQ(3, testObject->vectorGeodeticLatitudePZ90->size()); //проверка на наличие 3х элементов из 3х задаваемых
    EXPECT_EQ(3, testObject->vectorGeodeticLongitudePZ90->size());
    EXPECT_EQ(3, testObject->vectorRectangularXPZ90->size());
    EXPECT_EQ(3, testObject->vectorRectangularYPZ90->size());

    testObject->vectorGeodeticLatitudePZ90->clear();
    testObject->vectorGeodeticLongitudePZ90->clear();

    testObject->getMemberFromRectangularVector(0); //получаем первую прямоугольную координату
    rectXBeforeFirst = testObject->getRectangularX();
    std::cout << rectXBeforeFirst << std::endl;
    rectYBeforeFirst = testObject->getRectangularY();
    std::cout << rectYBeforeFirst << std::endl;

    testObject->getMemberFromRectangularVector(1); //вторая прямоугольная
    rectXBeforeSecond = testObject->getRectangularX();
    std::cout << rectXBeforeSecond << std::endl;
    rectYBeforeSecond = testObject->getRectangularY();
    std::cout << rectYBeforeSecond << std::endl;

    testObject->getMemberFromRectangularVector(2); //третья
    rectXBeforeThird = testObject->getRectangularX();
    std::cout << rectXBeforeThird << std::endl;
    rectYBeforeThird = testObject->getRectangularY();
    std::cout << rectYBeforeThird << std::endl;
    std::cout << std::endl;

    testObject->fromRectangularToGeodeticVector();

    EXPECT_EQ(3, testObject->vectorGeodeticLatitudePZ90->size()); //проверка на наличие 3х элементов из 3х задаваемых
    EXPECT_EQ(3, testObject->vectorGeodeticLongitudePZ90->size());
    EXPECT_EQ(3, testObject->vectorRectangularXPZ90->size());
    EXPECT_EQ(3, testObject->vectorRectangularYPZ90->size());

    testObject->vectorRectangularXPZ90->clear();
    testObject->vectorRectangularYPZ90->clear();

    testObject->getMemberFromGeodeticVector(0);
    latitudeAfterFirst = testObject->getGeodeticLatitudeB();
    std::cout << latitudeAfterFirst << std::endl;
    longitudeAfterFirst = testObject->getGeodeticLongitudeL();
    std::cout << longitudeAfterFirst << std::endl;

    testObject->getMemberFromGeodeticVector(1);
    latitudeAfterSecond = testObject->getGeodeticLatitudeB();
    std::cout << latitudeAfterSecond << std::endl;
    longitudeAfterSecond = testObject->getGeodeticLongitudeL();
    std::cout << longitudeAfterSecond << std::endl;

    testObject->getMemberFromGeodeticVector(2);
    latitudeAfterThird = testObject->getGeodeticLatitudeB();
    std::cout << latitudeAfterThird << std::endl;
    longitudeAfterThird = testObject->getGeodeticLongitudeL();
    std::cout << longitudeAfterThird << std::endl;

    EXPECT_EQ(round(latitudeBeforeFirst * 1000000) / 1000000, round(latitudeAfterFirst * 1000000) / 1000000);
    EXPECT_EQ(round(latitudeBeforeSecond * 1000000) / 1000000, round(latitudeAfterSecond * 1000000) / 1000000);
    EXPECT_EQ(round(latitudeBeforeThird * 1000000) / 1000000, round(latitudeAfterThird * 1000000) / 1000000);

    EXPECT_EQ(round(longitudeBeforeFirst * 1000000) / 1000000, round(longitudeAfterFirst * 1000000) / 1000000);
    EXPECT_EQ(round(longitudeBeforeSecond * 1000000) / 1000000, round(longitudeAfterSecond * 1000000) / 1000000);
    EXPECT_EQ(round(longitudeBeforeThird * 1000000) / 1000000, round(longitudeAfterThird * 1000000) / 1000000);

    testObject->fromGeodeticToRectangularVector();

    testObject->vectorGeodeticLatitudePZ90->clear();
    testObject->vectorGeodeticLongitudePZ90->clear();

    testObject->getMemberFromRectangularVector(0); //получаем первую прямоугольную координату
    rectXAfterFirst = testObject->getRectangularX();
    std::cout << rectXAfterFirst << std::endl;
    rectYAfterFirst = testObject->getRectangularY();
    std::cout << rectYAfterFirst << std::endl;

    testObject->getMemberFromRectangularVector(1); //вторая прямоугольная
    rectXAfterSecond = testObject->getRectangularX();
    std::cout << rectXAfterSecond << std::endl;
    rectYAfterSecond = testObject->getRectangularY();
    std::cout << rectYAfterSecond << std::endl;

    testObject->getMemberFromRectangularVector(2); //третья
    rectXAfterThird = testObject->getRectangularX();
    std::cout << rectXAfterThird << std::endl;
    rectYAfterThird = testObject->getRectangularY();
    std::cout << rectYAfterThird << std::endl;
    std::cout << std::endl;

    EXPECT_EQ(rectXBeforeFirst, rectXAfterFirst);
    EXPECT_EQ(rectXBeforeSecond, rectXAfterSecond);


    EXPECT_EQ(rectYBeforeFirst, rectYAfterFirst);


}

