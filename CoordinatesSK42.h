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

    void getMemberFromGeodeticVector(int) override;
    void getMemberFromRectangularVector(int) override;

    double getGeodeticLatitudeB() override; //не актуально
    double getGeodeticLongitudeL() override; //не актуально

    void setGeodeticCoordinates(double, double) override; //не актуально

    void geodeticToRectangular() override; //не актуально
    void rectangularToGeodetic() override; //не актуально

    void loadGeodeticToVector() override; //не актуально

    void fromGeodeticToRectangularVector() override; //не актуально
    void fromRectangularToGeodeticVector() override; //не актуально

    FRIEND_TEST(loadAndGetFromRectVectorTest, Equivalence);

public:
    double getRectangularX() override;
    double getRectangularY() override;

    void setRectangularCoordinates(double, double) override;

    void loadRectangularToVector() override;
};


#endif //COORDINATESEX_COORDINATESSK42_H
