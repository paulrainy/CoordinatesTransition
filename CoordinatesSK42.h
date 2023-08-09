//
// Created by paul on 07.08.23.
//

#ifndef COORDINATESEX_COORDINATESSK42_H
#define COORDINATESEX_COORDINATESSK42_H

#include "CoordinatesInterface.h"

class CoordinatesSK42 : protected CoordinatesInterface {
private:
    const double SEMI_MAJOR_AXIS_CONST = 6378245;
    //Большая полуось
    const double COMPRESSION_CONST = 1.0 / 298.3;
    //Сжатие общеземного эллипсоида

    //const double PI = 3.1415926535;

    double geodetic_latitude_B{};//геодезическая широта пз90 (B)
    double geodetic_longitude_L{}; //геодезическая долгота пз90 (L)
    double rectangular_X{}; // ось X пз90
    double rectangular_Y{}; // ось Y пз90

    void checkGeodeticNum(double, double) override;
public:
    double getGeodeticLatitudeB() override;
    double getGeodeticLongitudeL() override;
    double getRectangularX() override;
    double getRectangularY() override;

    void setGeodeticCoordinates(double, double) override;
    void setRectangularCoordinates(double, double) override;

    void geodeticToRectangular() override;
    void rectangularToGeodetic() override;
};


#endif //COORDINATESEX_COORDINATESSK42_H
