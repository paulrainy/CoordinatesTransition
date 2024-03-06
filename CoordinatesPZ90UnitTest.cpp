//
// Created by paul on 8/31/23.
//

#include <gtest/gtest.h>
#include <iostream>

#include "CoordinatesPZ90.h"

auto * testObjectPZ90 = new CoordinatesPZ90;

TEST(SetCoordinatesTests, Equivalence){ //тест сеттеров с геттерами
    testObjectPZ90->setGeodeticCoordinates(42 * M_PI / 180, 32 * M_PI / 180);
    EXPECT_EQ(42 * M_PI / 180, testObjectPZ90->getGeodeticLatitudeB());
    EXPECT_EQ(32, testObjectPZ90->getGeodeticLongitudeL());

    testObjectPZ90->setRectangularCoordinates(100000, 100000);
    EXPECT_EQ(100000, testObjectPZ90->getRectangularX());
    EXPECT_EQ(100000, testObjectPZ90->getRectangularY());
}

TEST(GeodeticToRectangularTransitionTest, EachSideEquivalence){ //тест перевода систем координат
    //вспомогательные переменные
    double latitudeBefore, latitudeAfter, longitudeBefore, longitudeAfter;
    double rectXBefore, rectXAfter, rectYBefore, rectYAfter;

    testObjectPZ90->setGeodeticCoordinates(42 * M_PI / 180, 32 * M_PI / 180);
    latitudeBefore = testObjectPZ90->getGeodeticLatitudeB();
    longitudeBefore = testObjectPZ90->getGeodeticLongitudeL();

    testObjectPZ90->geodeticToRectangular();//первый проход

    rectXBefore = testObjectPZ90->getRectangularX();
    rectYBefore = testObjectPZ90->getRectangularY();

    testObjectPZ90->rectangularToGeodetic();//первый обратный проход

    latitudeAfter = testObjectPZ90->getGeodeticLatitudeB();
    longitudeAfter = testObjectPZ90->getGeodeticLongitudeL();

    EXPECT_EQ(round(latitudeBefore * 1000000) / 1000000, round(latitudeAfter * 1000000) / 1000000);
    EXPECT_EQ(round(longitudeBefore * 1000000) / 1000000, round(longitudeAfter * 1000000) / 1000000);
    //погрешность соответствует требованию в 10^-6

    testObjectPZ90->geodeticToRectangular();//второй проход

    rectXAfter = testObjectPZ90->getRectangularX();
    rectYAfter = testObjectPZ90->getRectangularY();

    EXPECT_EQ(round(rectXBefore * 10000) / 10000, round(rectXAfter * 10000) / 10000);
    EXPECT_EQ(round(rectYBefore * 1000) / 1000, round(rectYAfter * 1000) / 1000);
}

TEST(sinHelpBTest, Equivalence){ //тест вспомогательного метода по возведению синуса в требуемую степень
    testObjectPZ90->setGeodeticCoordinates(42 * M_PI / 180, 32 * M_PI / 180);
    EXPECT_EQ(pow(sin(42 * M_PI / 180), 2), testObjectPZ90->sinHelpB(2));
}

//TEST(powHelpL2Test, Equivalence){ //тест вспомогательного метода
//    testObjectPZ90->setGeodeticCoordinates(42 * M_PI / 180, 32 * M_PI / 180);
//    testObjectPZ90->geodeticToRectangular();
//    EXPECT_EQ(pow(((testObjectPZ90->getGeodeticLongitudeL() - (3.0 + 6.0 * (static_cast<int>((6.0 +
//        testObjectPZ90->getGeodeticLongitudeL()) / 6.0) - 1.0))) / 57.29577951), 2), testObjectPZ90->powHelpL2());
//}

TEST(loadAndGetFromVectorTest, Equivalence){ //тест загрузки и выгрузки из вектора
    EXPECT_TRUE(testObjectPZ90->vectorGeodeticLatitudePZ90->empty()); //проверка на отсутствие элементов в векторе
    EXPECT_TRUE(testObjectPZ90->vectorGeodeticLongitudePZ90->empty());

    testObjectPZ90->setGeodeticCoordinates(42 * M_PI / 180, 32 * M_PI / 180); //создание геодезической координаты
    testObjectPZ90->loadGeodeticToVector(); //загрузка координаты в вектор
    testObjectPZ90->setGeodeticCoordinates(52 * M_PI / 180, 42 * M_PI / 180); //вторая координата
    testObjectPZ90->loadGeodeticToVector(); //загрузка в вектор

    EXPECT_FALSE(testObjectPZ90->vectorGeodeticLatitudePZ90->empty()); //проверка на наличие элементов в векторе
    EXPECT_FALSE(testObjectPZ90->vectorGeodeticLongitudePZ90->empty());

    testObjectPZ90->setRectangularCoordinates(100000, 200000); //создание прямоугольной координаты
    testObjectPZ90->loadRectangularToVector(); //загрузка в вектор
    testObjectPZ90->setRectangularCoordinates(3000000, 4000000); //вторая координата
    testObjectPZ90->loadRectangularToVector(); //загрузка

    EXPECT_FALSE(testObjectPZ90->vectorRectangularXPZ90->empty()); //проверка на наличие элементов в векторе
    EXPECT_FALSE(testObjectPZ90->vectorRectangularYPZ90->empty());

    testObjectPZ90->getMemberFromGeodeticVector(0); //возвращаем из вектора первую записанную координату

    EXPECT_EQ(42 * M_PI / 180, testObjectPZ90->getGeodeticLatitudeB()); //проверка на соответствие широты
    EXPECT_EQ(32, testObjectPZ90->getGeodeticLongitudeL()); //проверка на соответствие долготы

    testObjectPZ90->getMemberFromGeodeticVector(1); //возвращаем из вектора вторую координату

    EXPECT_EQ(52 * M_PI / 180, testObjectPZ90->getGeodeticLatitudeB()); //то же самое как и выше
    EXPECT_EQ(42, testObjectPZ90->getGeodeticLongitudeL());

    testObjectPZ90->getMemberFromRectangularVector(0);
    EXPECT_EQ(100000, testObjectPZ90->getRectangularX());
    EXPECT_EQ(200000, testObjectPZ90->getRectangularY());

    testObjectPZ90->getMemberFromRectangularVector(1);
    EXPECT_EQ(3000000, testObjectPZ90->getRectangularX());
    EXPECT_EQ(4000000, testObjectPZ90->getRectangularY());

    testObjectPZ90->vectorGeodeticLatitudePZ90->clear(); //очистка векторов для последующих тестов
    testObjectPZ90->vectorGeodeticLongitudePZ90->clear();
    testObjectPZ90->vectorRectangularXPZ90->clear();
    testObjectPZ90->vectorRectangularYPZ90->clear();
}

TEST(geodeticToRectangularVectorTransitionTest, EachSideEquivalence){
    //вспомогательные переменные
    double latitudeBeforeFirst, latitudeAfterFirst, longitudeBeforeFirst, longitudeAfterFirst;
    double latitudeBeforeSecond, latitudeAfterSecond, longitudeBeforeSecond, longitudeAfterSecond;
    double latitudeBeforeThird, latitudeAfterThird, longitudeBeforeThird, longitudeAfterThird;
    double rectXBeforeFirst, rectXAfterFirst, rectYBeforeFirst, rectYAfterFirst;
    double rectXBeforeSecond, rectXAfterSecond, rectYBeforeSecond, rectYAfterSecond;
    double rectXBeforeThird, rectXAfterThird, rectYBeforeThird, rectYAfterThird;

    testObjectPZ90->setGeodeticCoordinates(42 * M_PI / 180, 32 * M_PI / 180); //создание геодезической координаты
    latitudeBeforeFirst = testObjectPZ90->getGeodeticLatitudeB(); //запись во вспомогательную переменную
    std::cout << latitudeBeforeFirst << std::endl; //вывод для визуального удобства
    longitudeBeforeFirst = testObjectPZ90->getGeodeticLongitudeL();
    std::cout << longitudeBeforeFirst << std::endl;
    testObjectPZ90->loadGeodeticToVector(); //загрузка координаты в вектор

    testObjectPZ90->setGeodeticCoordinates(52 * M_PI / 180, 42 * M_PI / 180); //вторая координата
    latitudeBeforeSecond = testObjectPZ90->getGeodeticLatitudeB();
    std::cout << latitudeBeforeSecond << std::endl;
    longitudeBeforeSecond = testObjectPZ90->getGeodeticLongitudeL();
    std::cout << longitudeBeforeSecond << std::endl;
    testObjectPZ90->loadGeodeticToVector();

    testObjectPZ90->setGeodeticCoordinates(62 * M_PI / 180, 52 * M_PI / 180); //третья координата
    latitudeBeforeThird = testObjectPZ90->getGeodeticLatitudeB();
    std::cout << latitudeBeforeThird << std::endl;
    longitudeBeforeThird = testObjectPZ90->getGeodeticLongitudeL();
    std::cout << longitudeBeforeThird << std:: endl;
    std::cout << std::endl;

    testObjectPZ90->loadGeodeticToVector();

    EXPECT_FALSE(testObjectPZ90->vectorGeodeticLatitudePZ90->empty()); //проверка на наличие элементов в векторе
    EXPECT_FALSE(testObjectPZ90->vectorGeodeticLongitudePZ90->empty());

    testObjectPZ90->fromGeodeticToRectangularVector(); //перевод группы координат

    EXPECT_EQ(3, testObjectPZ90->vectorGeodeticLatitudePZ90->size()); //проверка на наличие 3х элементов из 3х задаваемых
    EXPECT_EQ(3, testObjectPZ90->vectorGeodeticLongitudePZ90->size());
    EXPECT_EQ(3, testObjectPZ90->vectorRectangularXPZ90->size());
    EXPECT_EQ(3, testObjectPZ90->vectorRectangularYPZ90->size());

    testObjectPZ90->vectorGeodeticLatitudePZ90->clear();
    testObjectPZ90->vectorGeodeticLongitudePZ90->clear();

    testObjectPZ90->getMemberFromRectangularVector(0); //получаем первую прямоугольную координату
    rectXBeforeFirst = testObjectPZ90->getRectangularX();
    std::cout << rectXBeforeFirst << std::endl;
    rectYBeforeFirst = testObjectPZ90->getRectangularY();
    std::cout << rectYBeforeFirst << std::endl;

    testObjectPZ90->getMemberFromRectangularVector(1); //вторая прямоугольная
    rectXBeforeSecond = testObjectPZ90->getRectangularX();
    std::cout << rectXBeforeSecond << std::endl;
    rectYBeforeSecond = testObjectPZ90->getRectangularY();
    std::cout << rectYBeforeSecond << std::endl;

    testObjectPZ90->getMemberFromRectangularVector(2); //третья
    rectXBeforeThird = testObjectPZ90->getRectangularX();
    std::cout << rectXBeforeThird << std::endl;
    rectYBeforeThird = testObjectPZ90->getRectangularY();
    std::cout << rectYBeforeThird << std::endl;
    std::cout << std::endl;

    testObjectPZ90->fromRectangularToGeodeticVector();

    EXPECT_EQ(3, testObjectPZ90->vectorGeodeticLatitudePZ90->size()); //проверка на наличие 3х элементов из 3х задаваемых
    EXPECT_EQ(3, testObjectPZ90->vectorGeodeticLongitudePZ90->size());
    EXPECT_EQ(3, testObjectPZ90->vectorRectangularXPZ90->size());
    EXPECT_EQ(3, testObjectPZ90->vectorRectangularYPZ90->size());

    testObjectPZ90->vectorRectangularXPZ90->clear();
    testObjectPZ90->vectorRectangularYPZ90->clear();

    testObjectPZ90->getMemberFromGeodeticVector(0);
    latitudeAfterFirst = testObjectPZ90->getGeodeticLatitudeB();
    std::cout << latitudeAfterFirst << std::endl;
    longitudeAfterFirst = testObjectPZ90->getGeodeticLongitudeL();
    std::cout << longitudeAfterFirst << std::endl;

    testObjectPZ90->getMemberFromGeodeticVector(1);
    latitudeAfterSecond = testObjectPZ90->getGeodeticLatitudeB();
    std::cout << latitudeAfterSecond << std::endl;
    longitudeAfterSecond = testObjectPZ90->getGeodeticLongitudeL();
    std::cout << longitudeAfterSecond << std::endl;

    testObjectPZ90->getMemberFromGeodeticVector(2);
    latitudeAfterThird = testObjectPZ90->getGeodeticLatitudeB();
    std::cout << latitudeAfterThird << std::endl;
    longitudeAfterThird = testObjectPZ90->getGeodeticLongitudeL();
    std::cout << longitudeAfterThird << std::endl;
    std::cout << std::endl;

    EXPECT_EQ(round(latitudeBeforeFirst * 1000000) / 1000000, round(latitudeAfterFirst * 1000000) / 1000000);
    EXPECT_EQ(round(latitudeBeforeSecond * 1000000) / 1000000, round(latitudeAfterSecond * 1000000) / 1000000);
    EXPECT_EQ(round(latitudeBeforeThird * 1000000) / 1000000, round(latitudeAfterThird * 1000000) / 1000000);

    EXPECT_EQ(round(longitudeBeforeFirst * 1000000) / 1000000, round(longitudeAfterFirst * 1000000) / 1000000);
    EXPECT_EQ(round(longitudeBeforeSecond * 1000000) / 1000000, round(longitudeAfterSecond * 1000000) / 1000000);
    EXPECT_EQ(round(longitudeBeforeThird * 1000000) / 1000000, round(longitudeAfterThird * 1000000) / 1000000);

    testObjectPZ90->fromGeodeticToRectangularVector();

    testObjectPZ90->vectorGeodeticLatitudePZ90->clear();
    testObjectPZ90->vectorGeodeticLongitudePZ90->clear();

    testObjectPZ90->getMemberFromRectangularVector(0); //получаем первую прямоугольную координату
    rectXAfterFirst = testObjectPZ90->getRectangularX();
    std::cout << rectXAfterFirst << std::endl;
    rectYAfterFirst = testObjectPZ90->getRectangularY();
    std::cout << rectYAfterFirst << std::endl;

    testObjectPZ90->getMemberFromRectangularVector(1); //вторая прямоугольная
    rectXAfterSecond = testObjectPZ90->getRectangularX();
    std::cout << rectXAfterSecond << std::endl;
    rectYAfterSecond = testObjectPZ90->getRectangularY();
    std::cout << rectYAfterSecond << std::endl;

    testObjectPZ90->getMemberFromRectangularVector(2); //третья
    rectXAfterThird = testObjectPZ90->getRectangularX();
    std::cout << rectXAfterThird << std::endl;
    rectYAfterThird = testObjectPZ90->getRectangularY();
    std::cout << rectYAfterThird << std::endl;
    std::cout << std::endl;

    EXPECT_EQ(round(rectXBeforeFirst * 1000) / 1000, round(rectXAfterFirst * 1000) / 1000);
    EXPECT_EQ(round(rectXBeforeSecond * 1000) / 1000, round(rectXAfterSecond * 1000) / 1000);
    EXPECT_EQ(round(rectXBeforeThird * 1000) / 1000, round(rectXAfterThird * 1000) / 1000);

    EXPECT_EQ(round(rectYBeforeFirst * 1000) / 1000, round(rectYAfterFirst * 1000) / 1000);
    EXPECT_EQ(round(rectYBeforeSecond * 1000) / 1000, round(rectYAfterSecond * 1000) / 1000);
    EXPECT_EQ(round(rectYBeforeThird * 1000) / 1000, round(rectYAfterThird * 1000) / 1000);

}

