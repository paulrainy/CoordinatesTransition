//
// Created by paul on 10.08.23.
//
//
//#ifndef COORDINATESEX_COORDINATESFACADE_H
//#define COORDINATESEX_COORDINATESFACADE_H
//
//#include "CoordinatesPZ90.h"
//#include "CoordinatesSK42.h"
//
//#include <vector>
//#include <iostream>
//
//class CoordinatesFacade {
//private:
//
//    std::vector<CoordinatesSK42> * vectorSK42 = new std::vector<CoordinatesSK42>;
//    //вектор, содержащий набор ск42
//
//public:
//    void objectCreatorGeodeticPZ90(double, double);
//    //метод, создающий объект с координатами и загружающий его в соответствующий вектор
//    void objectCreatorRectangularPZ90(double, double);
//    //метод, создающий объект с координатами и загружающий его в соответствующий вектор
//    void objectCreatorSK42(double, double);
//    //метод, создающий объект с координатами и загружающий его в соответствующий вектор
//
//    void vectorGeodeticToRectangular();
//    //перевод вектора с геодезическими координатами в плоские прямоугольные
//    void vectorRectangularToGeodetic();
//    //перевод вектора с плоскими координатами в геодезические
//
//    CoordinatesPZ90 getMemberVectorGeodeticPZ90(int);
//    //геттер, возвращающий элемент вектора под соответствующим номером
//    CoordinatesPZ90 getMemberVectorRectangularPZ90(int);
//    //геттер, возвращающий элемент вектора под соответствующим номером
//    CoordinatesSK42 getMemberVectorSK42(int);
//    //геттер, возвращающий элемент вектора под соответствующим номером
//
//
//
//};
//
//
//#endif //COORDINATESEX_COORDINATESFACADE_H
