//
// Created by paul on 02.08.23.
//

#ifndef COORDINATESEX_COORDINATESINTERFACE_H
#define COORDINATESEX_COORDINATESINTERFACE_H

#include <cmath>
#include <vector>
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

    virtual void getMemberFromGeodeticVector(int) = 0; //записывает элемент вектора для удобства
    virtual void getMemberFromRectangularVector(int) = 0; //записывает элемент вектора для удобства
    virtual void loadGeodeticToVector() = 0; //загрузка данных в векторы геодезических пз90
    virtual void loadRectangularToVector() = 0; //загрузка данных в векторы плоских прямоугольных пз90

    //проверка поступающих значений прямоугольных координат

    virtual void geodeticToRectangular() = 0; //преобразование географических в плоские
    virtual void rectangularToGeodetic() = 0; //преобразование плоских в графические

};

#endif //COORDINATESEX_COORDINATESINTERFACE_H