//
// Created by paul on 07.08.23.
//

#include "CoordinatesSK42.h"

double __attribute__((unused)) CoordinatesSK42::getGeodeticLatitudeB() {}

double __attribute__((unused)) CoordinatesSK42::getGeodeticLongitudeL() {}

double CoordinatesSK42::getRectangularX() {
    return rectangularX;
}

double CoordinatesSK42::getRectangularY() {
    return rectangularY;
}

void __attribute__((unused)) CoordinatesSK42::setGeodeticCoordinates(double, double) {}

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
    this->rectangularX = inputRectangularX;
    this->rectangularY = inputRectangularY;
}

void __attribute__((unused)) CoordinatesSK42::geodeticToRectangular() {}

void __attribute__((unused)) CoordinatesSK42::rectangularToGeodetic() {}

void __attribute__((unused)) CoordinatesSK42::getMemberFromGeodeticVector(int) {}

void CoordinatesSK42::getMemberFromRectangularVector(int vectorMember) {
    if (vectorRectangularXSK42->empty() || vectorRectangularYSK42->empty()){
        std::cout << "vector is empty!" << std::endl;
    }
    else{
        setRectangularCoordinates(vectorRectangularXSK42->at(vectorMember),
                                  vectorRectangularYSK42->at(vectorMember));
    }
}

void __attribute__((unused)) CoordinatesSK42::loadGeodeticToVector() {}

void CoordinatesSK42::loadRectangularToVector() {
    vectorRectangularXSK42->push_back(getRectangularX());
    vectorRectangularYSK42->push_back(getRectangularY());
}

void __attribute__((unused)) CoordinatesSK42::fromGeodeticToRectangularVector() {}

void __attribute__((unused)) CoordinatesSK42::fromRectangularToGeodeticVector() {}

int CoordinatesSK42::getSemiMajorAxisConst() {
    return SEMI_MAJOR_AXIS_CONST;
}

double CoordinatesSK42::getCompressionConst() {
    return COMPRESSION_CONST;
}

CoordinatesSK42::~CoordinatesSK42() = default;

CoordinatesSK42::CoordinatesSK42() = default;
