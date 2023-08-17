//
// Created by paul on 07.08.23.
//

#ifndef COORDINATESEX_COORDINATESSK42_H
#define COORDINATESEX_COORDINATESSK42_H

#include "CoordinatesInterface.h"

class CoordinatesSK42 : protected CoordinatesInterface {
private:
    //ск42 подразумевает использование только плоские прямоугольные координаты

    const double SEMI_MAJOR_AXIS_CONST = 6378245;
    //Большая полуось
    const double COMPRESSION_CONST = 1.0 / 298.3;
    //Сжатие общеземного эллипсоида

    double rectangular_X{}; // ось X
    double rectangular_Y{}; // ось Y

    void checkGeodeticNum(double, double) override; //не актуально
    void checkRectangularNum(double, double) override;

public:
    double getGeodeticLatitudeB() override; //не актуально
    double getGeodeticLongitudeL() override; //не актуально
    double getRectangularX() override;
    double getRectangularY() override;

    void setGeodeticCoordinates(double, double) override; //не актуально
    void setRectangularCoordinates(double, double) override;

    void geodeticToRectangular() override; //не актуально
    void rectangularToGeodetic() override; //не актуально
};


#endif //COORDINATESEX_COORDINATESSK42_H
