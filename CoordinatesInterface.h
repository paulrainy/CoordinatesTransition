//
// Created by paul on 02.08.23.
//

#ifndef COORDINATESEX_COORDINATESINTERFACE_H
#define COORDINATESEX_COORDINATESINTERFACE_H

#include <vector>
#include <cmath>

class CoordinatesInterface {
protected:
    //здесь находятся универсальные поля и методы!!!!!!!!
    double geodetic_latitude_B;//геодезическая широта пз90 (B)
    double geodetic_longitude_L; //геодезическая долгота пз90 (L)
    double rectangular_X; // ось X пз90
    double rectangular_Y; // ось Y пз90

    virtual double get_geodetic_latitude_B(); //геттер геодезической широты
    virtual double get_geodetic_longitude_L(); //геттер геодезической долготы
    virtual double get_rectangular_X();
    virtual double get_rectangular_Y();
    virtual void set_geodetic_coordinates(double, double); //сеттер для геодезических координат
    virtual void set_rectangular_coordinates(double, double); //сеттер для прямоугольных координат


//    std::vector <double> array_pz90_latitude; //вектор с координатами широты пз90
//    std::vector <double> array_pz90_longitude; //вектор с координатами долготы пз90
//    std::vector <double> array_sk42_X; //вектор с х абсциссами ск42
//    std::vector <double> array_sk42_Y; //вектор с y орднатами ск42

    virtual double get_sk42_X();
    virtual double get_sk42_Y();

    virtual void set_sk42(double, double);
    virtual void pz90_to_sk42(); //преобразование географических в плоские
    virtual void sk42_to_pz90(); //преобразование плоских в графические
    virtual void array_pz90_to_sk42(); //преобразование массива географических в плоские
    virtual void array_sk42_to_pz90(); //преобразование массива плоских в географические
    //
};

#endif //COORDINATESEX_COORDINATESINTERFACE_H