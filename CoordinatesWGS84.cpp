//
// Created by paul on 3/6/24.
//

#include "CoordinatesWGS84.h"

CoordinatesWGS84::CoordinatesWGS84() = default;

CoordinatesWGS84::~CoordinatesWGS84() = default;

double CoordinatesWGS84::getGeodeticLatitudeB() {
    return geodeticLatitudeB;
}

double CoordinatesWGS84::getGeodeticLongitudeL() {
    return geodeticLongitudeL;
}

void CoordinatesWGS84::setGeodeticCoordinates(double inputLatitudeB, double inputLongitudeL) {
    while(true) {
        if (inputLatitudeB < (-1.0 * M_PI / 2.0) || inputLatitudeB > (M_PI / 2.0)){
            std::cout << "wrong latitude! " << inputLatitudeB << " is incorrect num!" << std::endl;
            std::cout << "input a new num in radians:" << std::endl;
            std::cin >> inputLatitudeB;
        }
        else if (inputLongitudeL < ( -1 * M_PI) || inputLongitudeL > M_PI){
            std::cout << "wrong longitude! " << inputLongitudeL << " is incorrect num!" << std::endl;
            std::cout << "input a new num in radians:" << std::endl;
            std::cin >> inputLongitudeL;
        }
        else {
            break;
        }
    }
    this->geodeticLatitudeB = inputLatitudeB;
    this->geodeticLongitudeL = inputLongitudeL;
}

void CoordinatesWGS84::loadGeodeticToVector() {
    vectorGeodeticLatitudeWGS84->push_back(getGeodeticLatitudeB());
    vectorGeodeticLongitudeWGS84->push_back(getGeodeticLongitudeL());
}

void CoordinatesWGS84::getMemberFromGeodeticVector(int vectorMember) {
    if (vectorGeodeticLatitudeWGS84->empty() || vectorGeodeticLongitudeWGS84->empty()){
        std::cout << "vector is empty!" << std::endl;
    }
    else{
        setGeodeticCoordinates(vectorGeodeticLatitudeWGS84->at(vectorMember),
                               vectorGeodeticLongitudeWGS84->at(vectorMember));
    }
}

void __attribute__((unused)) CoordinatesWGS84::getMemberFromRectangularVector(int) {}

double __attribute__((unused)) CoordinatesWGS84::getRectangularX() {}

double __attribute__((unused)) CoordinatesWGS84::getRectangularY() {}

void __attribute__((unused)) CoordinatesWGS84::geodeticToRectangular() {}

void __attribute__((unused)) CoordinatesWGS84::rectangularToGeodetic() {}

void __attribute__((unused)) CoordinatesWGS84::loadRectangularToVector() {}

void __attribute__((unused)) CoordinatesWGS84::fromGeodeticToRectangularVector() {}

void __attribute__((unused)) CoordinatesWGS84::fromRectangularToGeodeticVector() {}

void __attribute__((unused)) CoordinatesWGS84::setRectangularCoordinates(double, double) {}

int CoordinatesWGS84::getSemiMajorAxisConst() {
    return SEMI_MAJOR_AXIS_CONST;
}

double CoordinatesWGS84::getCompressionConst() {
    return COMPRESSION_CONST;
}

double CoordinatesWGS84::getGeodeticHeightH() {
    return geodeticHeightH;
}
