//
// Created by paul on 07.08.23.
//

#ifndef COORDINATESEX_COORDINATESSK42_H
#define COORDINATESEX_COORDINATESSK42_H

#include <gtest/gtest.h>

#include "CoordinatesInterface.h"

class CoordinatesSK42 : protected CoordinatesInterface {
private:
    //ск42 подразумевает использование только плоских прямоугольных координат
    const double SEMI_MAJOR_AXIS_CONST = 6378245;
    //Большая полуось
    const double COMPRESSION_CONST = 1.0 / 298.3;
    //Сжатие общеземного эллипсоида

    double rectangular_X{}; // ось X
    double rectangular_Y{}; // ось Y

    std::vector<double> * vectorRectangularXSK42 = new std::vector<double>;
    //вектор, содержащий набор плоских прямоугольных координат X ск42
    std::vector<double> * vectorRectangularYSK42 = new std::vector<double>;
    //вектор, содержащий набор плоских прямоугольных координат Y ск42

    void __attribute__((unused)) getMemberFromGeodeticVector(int) override;

    void getMemberFromRectangularVector(int) override;

    double __attribute__((unused)) getGeodeticLatitudeB() override;
    double __attribute__((unused)) getGeodeticLongitudeL() override;

    void __attribute__((unused)) setGeodeticCoordinates(double, double) override;

    void __attribute__((unused)) geodeticToRectangular() override;
    void __attribute__((unused)) rectangularToGeodetic() override;

    void __attribute__((unused)) loadGeodeticToVector() override;

    void __attribute__((unused)) fromGeodeticToRectangularVector() override;
    void __attribute__((unused)) fromRectangularToGeodeticVector() override;

    FRIEND_TEST(loadAndGetFromRectVectorTest, Equivalence);

public:
    CoordinatesSK42();
    ~CoordinatesSK42();

    double getRectangularX() override;
    double getRectangularY() override;

    void setRectangularCoordinates(double, double) override;

    void loadRectangularToVector() override;
};


#endif //COORDINATESEX_COORDINATESSK42_H
