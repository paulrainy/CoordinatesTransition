//
// Created by paul on 29.11.23.
//

#include "CoordinatesTranslation.h"


void CoordinatesTranslation::setCoordinateObjectPZ90(double inputCoordinateFirst, double inputCoordinateSecond, bool isGeodetic) {
    if (isGeodetic)
        coordinateObjectPZ90.setGeodeticCoordinates(inputCoordinateFirst, inputCoordinateSecond);
    else
        coordinateObjectPZ90.setRectangularCoordinates(inputCoordinateFirst, inputCoordinateSecond);
}

void CoordinatesTranslation::setCoordinateObjectSK42(double inputRectX, double inputRectY) {
    coordinateObjectSK42.setRectangularCoordinates(inputRectX, inputRectY);
}

void CoordinatesTranslation::setCoordinateObjectWGS84(double inputLatitudeB, double inputLongitudeL) {
    coordinateObjectWGS84.setGeodeticCoordinates(inputLatitudeB, inputLongitudeL);
}

CoordinatesPZ90 CoordinatesTranslation::getCoordinateObjectPZ90() {
    return coordinateObjectPZ90;
}

CoordinatesSK42 CoordinatesTranslation::getCoordinateObjectSK42() {
    return coordinateObjectSK42;
}

CoordinatesWGS84 CoordinatesTranslation::getCoordinateObjectWGS84() {
    return coordinateObjectWGS84;
}

void CoordinatesTranslation::PZ90toSK42() {
    coordinateObjectPZ90.geodeticToRectangular();
    coordinateObjectSK42.setRectangularCoordinates(coordinateObjectPZ90.getRectangularX(), coordinateObjectPZ90.getRectangularY());
}

void CoordinatesTranslation::SK42toPZ90() {
//    std::vector<std::vector<double>> angularTransformationElements = {
//            {1.0, -3,850439 * pow(10, -6), 1.679685 * pow(10, -6)},
//            {3,850439 * pow(10, -6), 1.0, -1.115071 * pow(10, -8)},
//            {-1.679685 * pow(10, -6), 1.115071 * pow(10, -8), 1.0}
//    };
//    std::vector<double> deltaElements = {23.557, -140.844, -79.778};
//    const double mElement = -0.228 * pow(10, -6);
    coordinateObjectPZ90.setRectangularCoordinates(coordinateObjectSK42.getRectangularX(), coordinateObjectSK42.getRectangularY());
    coordinateObjectPZ90.rectangularToGeodetic();
}

void CoordinatesTranslation::PZ90toWGS84() {
//    // Получаем текущие координаты
//    double latitude = getGeodeticLatitudeB();
//    double longitude = getGeodeticLongitudeL();
//
//    // Конвертируем координаты из ПЗ-90.11 в WGS84
//    double latitudeWGS84 = latitude - 0.00036;
//    double longitudeWGS84 = longitude + 0.00018;
//
//    // Устанавливаем новые координаты
//    setGeodeticCoordinates(latitudeWGS84, longitudeWGS84);

}

void CoordinatesTranslation::WGS84toPZ90() {

}

void CoordinatesTranslation::WGS84toSK42() {

}

void CoordinatesTranslation::SK42toWGS84() {

}
