//
// Created by paul on 07.08.23.
//

#include "CoordinatesSK42.h"

void CoordinatesSK42::checkGeodeticNum(double test_num1, double test_num_2) {
    try {
        if (test_num1 < -90 || test_num1 > 90) throw std::exception();
        if (test_num_2 < -180 || test_num_2 > 180) throw std::exception();
    }
    catch (std::exception()){
        std::cout << "wrong latitude or longitude!" << std::endl;
        geodetic_latitude_B = NULL;
        geodetic_longitude_L = NULL;
    }
}

double CoordinatesSK42::getGeodeticLatitudeB() {
    return geodetic_latitude_B;
}

double CoordinatesSK42::getGeodeticLongitudeL() {
    return geodetic_longitude_L;
}

double CoordinatesSK42::getRectangularX() {
    return rectangular_X;
}

double CoordinatesSK42::getRectangularY() {
    return rectangular_Y;
}

void CoordinatesSK42::setGeodeticCoordinates(double, double) {

}

void CoordinatesSK42::setRectangularCoordinates(double, double) {

}

void CoordinatesSK42::geodeticToRectangular() {

}

void CoordinatesSK42::rectangularToGeodetic() {

}
