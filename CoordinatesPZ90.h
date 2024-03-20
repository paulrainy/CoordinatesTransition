//
// Created by paul on 03.08.23.
//

#ifndef COORDINATESEX_COORDINATESPZ90_H
#define COORDINATESEX_COORDINATESPZ90_H

#include "CoordinatesInterface.h"

class CoordinatesPZ90 : protected CoordinatesInterface{
private:
    const double GEOCENTRIC_GRAVITATIONAL_CONST = 398600.4418; //Геоцентрическая гравитационная постоянная Земли (с учетом атмосферы) (fM)
    const double ANGULAR_VELOCITY_CONST = 7.292115 * pow(10, -5); //Угловая скорость вращения Земли
    const int SEMI_MAJOR_AXIS_CONST = 6378136; //Большая полуось
    const double COMPRESSION_CONST = 1.0 / 298.25784; //Сжатие общеземного эллипсоида

    double geodeticLatitudeB{};//геодезическая широта пз90 (B)
    double geodeticLongitudeL{}; //геодезическая долгота пз90 (L)
    double geodeticHeightH{};
    double rectangularX{}; // ось X пз90
    double rectangularY{}; // ось Y пз90

    //вспомогательные переменные для формул перевода
    double geoB{}, geoL{}, geoDistL{}, geoAnswX{}, geoAnswY{};
    int geoZoneN{}, rectZoneN{};
    double rectDeltaB{}, rectDistL{}, rectHelpBeta{}, rectHelpB0{}, rectHelpZ{}, rectAnswB{}, rectAnswL{};

    //вектор, содержащий набор геодезических широт пз90
    std::vector<double> * vectorGeodeticLatitudePZ90 = new std::vector<double>;
    //вектор, содержащий набор геодезических долгот пз90
    std::vector<double> * vectorGeodeticLongitudePZ90 = new std::vector<double>;
    //вектор, содержащий набор плоских прямоугольных координат X пз90
    std::vector<double> * vectorRectangularXPZ90 = new std::vector<double>;
    //вектор, содержащий набор плоских прямоугольных координат Y пз90
    std::vector<double> * vectorRectangularYPZ90 = new std::vector<double>;

    double sinHelpB(int); //метод, сокращающий подсчёты синусов широты и долготы в соответствующих формулах перевода
    double powHelpL2() const; //метод, сокращающий подсчёты степени числа l

    void getMemberFromGeodeticVector(int) override;
    void getMemberFromRectangularVector(int) override;

    //необходимо для тестирования приватных методов
    FRIEND_TEST(sinHelpBTest, Equivalence);
    FRIEND_TEST(powHelpL2Test, Equivalence);
    FRIEND_TEST(loadAndGetFromVectorTest, Equivalence);
    FRIEND_TEST(geodeticToRectangularVectorTransitionTest, EachSideEquivalence);

public:
    CoordinatesPZ90();
    ~CoordinatesPZ90();

    int getSemiMajorAxisConst() override;
    double getCompressionConst() override;

    double getGeodeticLatitudeB() override;
    double getGeodeticLongitudeL() override;
    double getGeodeticHeightH() override;
    double getRectangularX() override;
    double getRectangularY() override;

    void setGeodeticCoordinates(double, double) override;
    void setRectangularCoordinates(double, double) override;

    void geodeticToRectangular() override;
    void rectangularToGeodetic() override;

    void loadGeodeticToVector() override;
    void loadRectangularToVector() override;

    void fromGeodeticToRectangularVector() override;
    void fromRectangularToGeodeticVector() override;
};

#endif //COORDINATESEX_COORDINATESPZ90_H
