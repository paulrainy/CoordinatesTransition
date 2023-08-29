//
// Created by paul on 07.08.23.
//

#include "CoordinatesSK42.h"

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

void CoordinatesSK42::setRectangularCoordinates(double inputRectangularX, double inputRectangularY) {
    while(true){
        if (inputRectangularX > 10002137 || inputRectangularX < -10002137) {
            std::cout << "wrong X!" << std::endl;
            std::cout << "input a new num in m:" << std::endl;
            std::cin >> inputRectangularX;
        }
        else if (inputRectangularY > 20037500 || inputRectangularY < -20037500){
            std::cout << "wrong Y!" << std::endl;
            std::cout << "input a new num in m:" << std::endl;
            std::cin >> inputRectangularY;
        }
        else{
            break;
        }
    }
    this->rectangular_X = inputRectangularX;
    this->rectangular_Y = inputRectangularY;
}

void CoordinatesSK42::geodeticToRectangular() {
    //неактуально для ск42
}

void CoordinatesSK42::rectangularToGeodetic() {
    //неактуально для ск42
}

void CoordinatesSK42::getMemberFromGeodeticVector(int) {

}

void CoordinatesSK42::getMemberFromRectangularVector(int) {

}

void CoordinatesSK42::loadGeodeticToVector() {

}

void CoordinatesSK42::loadRectangularToVector() {

}
