//
// Created by paul on 07.08.23.
//

#include "CoordinatesSK42.h"

void CoordinatesSK42::checkGeodeticNum(double, double) {
    //неактуально для ск42
}

double CoordinatesSK42::getGeodeticLatitudeB() {
    return 0;
    //неактуально для ск42
}

double CoordinatesSK42::getGeodeticLongitudeL() {
    return 0;
    //неактуально для ск42
}

double CoordinatesSK42::getRectangularX() {
    return rectangular_X;
}

double CoordinatesSK42::getRectangularY() {
    return rectangular_Y;
}

void CoordinatesSK42::setGeodeticCoordinates(double, double) {
    //неактуально для ск42
}

void CoordinatesSK42::setRectangularCoordinates(double inputRectX, double inputRectY) {
    this->rectangular_X = inputRectX;
    this->rectangular_Y = inputRectY;
}

void CoordinatesSK42::geodeticToRectangular() {
    //неактуально для ск42
}

void CoordinatesSK42::rectangularToGeodetic() {
    //неактуально для ск42
}

void CoordinatesSK42::checkRectangularNum(double testNum1, double testNum2) {
    try {
        std::string errorMessage;
        if (testNum1 > 10002137 || testNum1 < -10002137) {
            errorMessage = "wrong X!";
            throw errorMessage;
        }
        if (testNum2 > 20037500 || testNum2 < -20037500){
            errorMessage = "wrong Y!";
            throw errorMessage;
        }
    }
    catch (std::string errorMessage) {
        std::cout << errorMessage << std::endl;
        delete [] this;
    }
}
