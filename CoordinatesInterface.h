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
    double geodetic_latitude_B{};//геодезическая широта пз90 (B)
    double geodetic_longitude_L{}; //геодезическая долгота пз90 (L)
    double rectangular_X{}; // ось X пз90
    double rectangular_Y{}; // ось Y пз90

    virtual double get_geodetic_latitude_B() = 0; //геттер геодезической широты
    virtual double get_geodetic_longitude_L() = 0; //геттер геодезической долготы
    virtual double get_rectangular_X() = 0; //геттер прямоугольного X
    virtual double get_rectangular_Y() = 0; //геттер прямоугольного Y

    virtual void set_geodetic_coordinates(double, double) = 0; //сеттер для геодезических координат
    virtual void set_rectangular_coordinates(double, double) = 0; //сеттер для прямоугольных координат

    virtual void geodetic_to_rectangular(double, double) = 0; //преобразование географических в плоские
    virtual void rectangular_to_geodetic(double, double) = 0; //преобразование плоских в графические
//    std::vector <double> array_pz90_latitude; //вектор с координатами широты пз90
//    std::vector <double> array_pz90_longitude; //вектор с координатами долготы пз90
//    std::vector <double> array_sk42_X; //вектор с х абсциссами ск42
//    std::vector <double> array_sk42_Y; //вектор с y орднатами ск42

};

#endif //COORDINATESEX_COORDINATESINTERFACE_H