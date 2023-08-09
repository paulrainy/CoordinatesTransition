//
// Created by paul on 02.08.23.
//

#ifndef COORDINATESEX_COORDINATESINTERFACE_H
#define COORDINATESEX_COORDINATESINTERFACE_H

#include <vector>
#include <cmath>
#include <iostream>

class CoordinatesInterface {
protected:
    //здесь находятся универсальные методы!
    virtual double getGeodeticLatitudeB() = 0; //геттер геодезической широты
    virtual double getGeodeticLongitudeL() = 0; //геттер геодезической долготы
    virtual double getRectangularX() = 0; //геттер прямоугольного X
    virtual double getRectangularY() = 0; //геттер прямоугольного Y

    virtual void setGeodeticCoordinates(double, double) = 0; //сеттер для геодезических координат
    virtual void setRectangularCoordinates(double, double) = 0; //сеттер для прямоугольных координат

    virtual void checkGeodeticNum(double, double) = 0;

    virtual void geodeticToRectangular() = 0; //преобразование географических в плоские
    virtual void rectangularToGeodetic() = 0; //преобразование плоских в графические
//    std::vector <double> array_pz90_latitude; //вектор с координатами широты пз90
//    std::vector <double> array_pz90_longitude; //вектор с координатами долготы пз90
//    std::vector <double> array_sk42_X; //вектор с х абсциссами ск42
//    std::vector <double> array_sk42_Y; //вектор с y орднатами ск42

};

#endif //COORDINATESEX_COORDINATESINTERFACE_H