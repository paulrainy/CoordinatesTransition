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

void CoordinatesTranslation::geodeticToSpatial(int semiMajorAxisConst, double compressionConst, double geodeticLatitudeB, double geodeticLongitudeL, double geodeticHeightH) {
    double eccentricitySquared = 2 * compressionConst - pow(compressionConst, 2);
    double firstVerticalCurvature = semiMajorAxisConst /
            (1 - eccentricitySquared * pow(sin(geodeticLatitudeB), 2));
    tempSpatialX = (firstVerticalCurvature + geodeticHeightH) * cos(geodeticLatitudeB) * cos(geodeticLongitudeL);
    tempSpatialY = (firstVerticalCurvature + geodeticHeightH) * cos(geodeticLatitudeB) * sin(geodeticLongitudeL);
    tempSpatialZ = ((1 - eccentricitySquared) * firstVerticalCurvature + geodeticHeightH) * sin(geodeticLatitudeB);
}

void CoordinatesTranslation::spacialToGeodetic(int semiMajorAxisConst, double compressionConst, double spatialX, double spatialY, double spatialZ) {
    double eccentricitySquared = 2 * compressionConst - pow(compressionConst, 2);
    //1 ход
    double helpD = sqrt(pow(spatialX, 2) + pow(spatialY, 2));
    //2 ход
    if (helpD == 0){
        tempGeodeticLatitudeB = (M_PI / 2) * (spatialZ / abs(spatialZ));
        tempGeodeticLongitudeL = 0;
        tempGeodeticHeightH = spatialZ * sin(tempGeodeticLatitudeB) - semiMajorAxisConst *
                sqrt(1 - eccentricitySquared * pow(sin(tempGeodeticLatitudeB), 2));
    }
    else{
        double helpLa = abs(asin(spatialY / helpD));
        if (spatialY < 0){
            if (spatialX > 0) {
                tempGeodeticLongitudeL = 2 * M_PI - helpLa;
            }
            else{
                tempGeodeticLongitudeL = M_PI + helpLa;
            }
        }
        else if (spatialY > 0){
            if (spatialX < 0){
                tempGeodeticLongitudeL = M_PI - helpLa;
            }
            else{
                tempGeodeticLongitudeL = helpLa;
            }
        }
        else{
            if (spatialX < 0){
                tempGeodeticLongitudeL = M_PI;
            }
            else{
                tempGeodeticLongitudeL = 0;
            }
        }
    }
    //3 ход
    if (spatialZ == 0){
        tempGeodeticLatitudeB = 0;
        tempGeodeticHeightH = helpD - semiMajorAxisConst;
    }
    else{
        double helpR = sqrt(pow(spatialX, 2) + pow(spatialY, 2) + pow(spatialZ, 2));
        double helpC = asin(spatialZ / helpR);
        double helpRo = (eccentricitySquared * semiMajorAxisConst) / (2 * helpR);
        double helpS1 = 0;
        double helpS2{}, helpB{}, checkD{};

        while(true){
            helpB = helpC + helpS1;
            helpS2 = asin((helpRo * sin(2 * helpB)) / sqrt(1.0 - eccentricitySquared * pow(sin(helpB), 2)));
            checkD = abs(helpS2 - helpS1);
            if (checkD < pow(10, -4)){
                tempGeodeticLatitudeB = helpB;
                tempGeodeticHeightH = helpD * cos(tempGeodeticLatitudeB) + spatialZ * sin(tempGeodeticLatitudeB) -
                        semiMajorAxisConst * sqrt(1 - eccentricitySquared * pow(sin(tempGeodeticLatitudeB), 2));
                break;
            }
            else{
                helpS1 = helpS2;
            }
        }
    }
}

std::vector<std::vector<double>> CoordinatesTranslation::getCoeffMatrix(double inputPhiX, double inputPhiY, double inputPhiZ) {
    std::vector<std::vector<double>> matrix = {
            {1.0, inputPhiZ, -1.0 * inputPhiY},
            {-1.0 * inputPhiZ, 1.0, inputPhiX},
            {inputPhiY, -1.0 * inputPhiX, 1.0}
    };
    return matrix;
}

std::vector<double> CoordinatesTranslation::multiplyMatrix(std::vector<std::vector<double>> coeffMatrix, std::vector<double> coordMatrix) {
    std::vector<double> resultMatrix;
    for (auto i = 0; i < 3; i++){
        double tempResult = 0;
        for (auto j = 0; j < 3; j++){
            tempResult += coeffMatrix[i][j] * coordMatrix[j];
        }
        resultMatrix.push_back(tempResult);
    }
    return resultMatrix;
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
    //заполняем коэффициенты
    phiX = -1.115071 * pow(10, -8);
    phiY = 1.716240 * pow(10, -8);
    phiZ = -2.041066 * pow(10, -8);
    deltaX = -0.013;
    deltaY = 0.106;
    deltaZ = 0.022;
    double helpM = -0.008 * pow(10, -6);
    //получаем матрицу коэффициентов
    std::vector<std::vector<double>> phiCoefficients = getCoeffMatrix(phiX, phiY, phiZ);
    //переводим координаты из геодезических в пространственные
    this->geodeticToSpatial(coordinateObjectPZ90.getSemiMajorAxisConst(), coordinateObjectPZ90.getCompressionConst(),
                      coordinateObjectPZ90.getGeodeticLatitudeB(), coordinateObjectPZ90.getGeodeticLongitudeL(),
                      coordinateObjectPZ90.getGeodeticHeightH());

    //задаём матрицу с пространственными координатами
    std::vector<double> spatialMatrix = {tempSpatialX, tempSpatialY, tempSpatialZ};
    //перемножаем матрицу с коэффициентами и изначальными координатами
    std::vector<double> midMatrix = multiplyMatrix(phiCoefficients, spatialMatrix);
    //умножаем каждый элемент промежуточной матрицы на 1-m
    for (auto i = 0; i < 3; i++){
        midMatrix[i] *= (1 - helpM);
    }
    //вычитаем дельты
    midMatrix[0] -= deltaX;
    midMatrix[1] -= deltaY;
    midMatrix[2] -= deltaZ;
    //переводим пространственные координаты в геодезические
    this->spacialToGeodetic(coordinateObjectWGS84.getSemiMajorAxisConst(), coordinateObjectWGS84.getCompressionConst(),
                      midMatrix[0], midMatrix[1], midMatrix[2]);

    //записываем значения в соответствующий объект
    coordinateObjectWGS84.setGeodeticCoordinates(tempGeodeticLatitudeB, tempGeodeticLongitudeL);
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



