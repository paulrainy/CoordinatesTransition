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

void CoordinatesTranslation::geodeticToSpatial(int semiMajorAxisConst, double compressionConst,
                                               double geodeticLatitudeB, double geodeticLongitudeL, double geodeticHeightH) {
    double eccentricitySquared = 2 * compressionConst - pow(compressionConst, 2);
    double firstVerticalCurvature = semiMajorAxisConst /
            (1 - eccentricitySquared * pow(sin(geodeticLatitudeB), 2));
    tempSpatialX = (firstVerticalCurvature + geodeticHeightH) * cos(geodeticLatitudeB) * cos(geodeticLongitudeL);
    tempSpatialY = (firstVerticalCurvature + geodeticHeightH) * cos(geodeticLatitudeB) * sin(geodeticLongitudeL);
    tempSpatialZ = ((1 - eccentricitySquared) * firstVerticalCurvature + geodeticHeightH) * sin(geodeticLatitudeB);
}

void CoordinatesTranslation::spacialToGeodetic(int semiMajorAxisConst, double compressionConst) {
    double eccentricitySquared = 2 * compressionConst - pow(compressionConst, 2);
    double helpD = sqrt(pow(tempSpatialX, 2) + pow(tempSpatialX, 2));
    if (helpD ==0){
        tempGeodeticLatitudeB = (M_PI /2) * (tempSpatialZ / abs(tempSpatialZ));
        tempGeodeticLongitudeL = 0;
        tempGeodeticHeightH = tempSpatialZ * sin(tempGeodeticLatitudeB) - semiMajorAxisConst *
                sqrt(1 - eccentricitySquared * pow(sin(tempGeodeticLatitudeB), 2));
    }
    else{
        double helpLa = abs(asin(tempSpatialY / helpD));
        //далее по госту условия
    }
}

void CoordinatesTranslation::PZ90toSK42() {
    coordinateObjectPZ90.geodeticToRectangular();
    coordinateObjectSK42.setRectangularCoordinates(coordinateObjectPZ90.getRectangularX(), coordinateObjectPZ90.getRectangularY());
}

void CoordinatesTranslation::SK42toPZ90() {
    coordinateObjectPZ90.setRectangularCoordinates(coordinateObjectSK42.getRectangularX(), coordinateObjectSK42.getRectangularY());
    coordinateObjectPZ90.rectangularToGeodetic();
}

void CoordinatesTranslation::PZ90toWGS84() {
    this->geodeticToSpatial(coordinateObjectPZ90.getSemiMajorAxisConst(), coordinateObjectPZ90.getCompressionConst(),
                      coordinateObjectPZ90.getGeodeticLatitudeB(), coordinateObjectPZ90.getGeodeticLongitudeL(),
                      coordinateObjectPZ90.getGeodeticHeightH());

}

void CoordinatesTranslation::WGS84toPZ90() {
    coordinateObjectPZ90.setGeodeticCoordinates(
            coordinateObjectWGS84.getGeodeticLatitudeB() + 0.00036, coordinateObjectWGS84.getGeodeticLongitudeL() - 0.00018);
}

void CoordinatesTranslation::WGS84toSK42() {
    coordinateObjectPZ90.setGeodeticCoordinates(
            coordinateObjectWGS84.getGeodeticLatitudeB() + 0.00036, coordinateObjectWGS84.getGeodeticLongitudeL() - 0.00018);
    this->PZ90toSK42();
}

void CoordinatesTranslation::SK42toWGS84() {
    this->SK42toPZ90();
    coordinateObjectWGS84.setGeodeticCoordinates(
            coordinateObjectPZ90.getGeodeticLatitudeB() - 0.00036, coordinateObjectPZ90.getGeodeticLongitudeL() + 0.00018);
}

