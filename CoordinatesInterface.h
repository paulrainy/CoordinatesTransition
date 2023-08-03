//
// Created by paul on 02.08.23.
//

#ifndef COORDINATESEX_COORDINATESINTERFACE_H
#define COORDINATESEX_COORDINATESINTERFACE_H

#include <vector>
#include <cmath>

class CoordinatesInterface {
protected:
    double pz90_latitude;//широта пз90
    double pz90_longitude; //долгота пз90
    double sk42_X; //x абсцисса по ск42
    double sk42_Y; //y ордната по ск42
    std::vector <double> array_pz90_latitude; //вектор с координатами широты пз90
    std::vector <double> array_pz90_longitude; //вектор с координатами долготы пз90
    std::vector <double> array_sk42_X; //вектор с х абсциссами ск42
    std::vector <double> array_sk42_Y; //вектор с y орднатами ск42

    virtual double get_pz90_latitude(); //геттеры
    virtual double get_pz90_longitude();
    virtual double get_sk42_X();
    virtual double get_sk42_Y();
    virtual void set_pz90(double, double); //сеттеры
    virtual void set_sk42(double, double);
    virtual void pz90_to_sk42(); //преобразование географических в плоские
    virtual void sk42_to_pz90(); //преобразование плоских в графические
    virtual void array_pz90_to_sk42(); //преобразование массива географических в плоские
    virtual void array_sk42_to_pz90(); //преобразование массива плоских в географические
    //
};

#endif //COORDINATESEX_COORDINATESINTERFACE_H