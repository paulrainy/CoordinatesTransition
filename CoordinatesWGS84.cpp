//
// Created by paul on 3/6/24.
//

#include "CoordinatesWGS84.h"

CoordinatesWGS84::CoordinatesWGS84() = default;

CoordinatesWGS84::~CoordinatesWGS84() = default;

double CoordinatesWGS84::getGeodeticLatitudeB() {
    return 0;
}

double CoordinatesWGS84::getGeodeticLongitudeL() {
    return 0;
}

void CoordinatesWGS84::setGeodeticCoordinates(double, double) {

}

void CoordinatesWGS84::loadGeodeticToVector() {

}

void CoordinatesWGS84::getMemberFromGeodeticVector(int) {

}

void __attribute__((unused)) CoordinatesWGS84::getMemberFromRectangularVector(int) {}

double __attribute__((unused)) CoordinatesWGS84::getRectangularX() {}

double __attribute__((unused)) CoordinatesWGS84::getRectangularY() {}

void __attribute__((unused)) CoordinatesWGS84::geodeticToRectangular() {}

void __attribute__((unused)) CoordinatesWGS84::rectangularToGeodetic() {}

void __attribute__((unused)) CoordinatesWGS84::loadRectangularToVector() {}

void __attribute__((unused)) CoordinatesWGS84::fromGeodeticToRectangularVector() {}

void __attribute__((unused)) CoordinatesWGS84::fromRectangularToGeodeticVector() {}
