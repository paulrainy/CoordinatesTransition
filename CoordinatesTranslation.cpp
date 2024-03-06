//
// Created by paul on 29.11.23.
//

#include "CoordinatesTranslation.h"


void CoordinatesTranslation::setCoordinateObjectPZ90(CoordinatesPZ90 inputObject) {

}

void CoordinatesTranslation::setCoordinateObjectSK42(CoordinatesSK42 inputObject) {

}

void CoordinatesTranslation::setCoordinateObjectWGS84(double inputObject) {

}

CoordinatesPZ90 CoordinatesTranslation::getCoordinateObjectPZ90() {
    return coordinateObjectPZ90;
}

CoordinatesSK42 CoordinatesTranslation::getCoordinateObjectSK42() {
    return coordinateObjectSK42;
}

double CoordinatesTranslation::getCoordinateObjectWGS84() {
    return coordinateObjectWGS84;
}

void CoordinatesTranslation::PZ90toSK42() {

}

void CoordinatesTranslation::WGS84toSK42() {

}

void CoordinatesTranslation::SK42toPZ90() {
    std::vector<std::vector<double>> angularTransformationElements = {
            {1.0, -3,850439 * pow(10, -6), 1.679685 * pow(10, -6)},
            {3,850439 * pow(10, -6), 1.0, -1.115071 * pow(10, -8)},
            {-1.679685 * pow(10, -6), 1.115071 * pow(10, -8), 1.0}
    };
    std::vector<double> deltaElements = {23.557, -140.844, -79.778};
    const double mElement = -0.228 * pow(10, -6);
}

void CoordinatesTranslation::WGS84toPZ90() {

}

void CoordinatesTranslation::PZ90toWGS84() {

}

void CoordinatesTranslation::SK42toWGS84() {

}
