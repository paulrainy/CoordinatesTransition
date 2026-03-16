//
// Created by paul on 03.08.23.
//

#include "CoordinatesPZ90.h"

double CoordinatesPZ90::getGeodeticLatitudeB() {
    return geodeticLatitudeB;
}

double CoordinatesPZ90::getGeodeticLongitudeL() {
    return geodeticLongitudeL;
}

double CoordinatesPZ90::getRectangularX() {
    return rectangularX;
}

double CoordinatesPZ90::getRectangularY() {
    return rectangularY;
}

void CoordinatesPZ90::setGeodeticCoordinates(double inputLatitudeB, double inputLongitudeL) {
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

void CoordinatesPZ90::setRectangularCoordinates(double inputRectangularX, double inputRectangularY) {
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

double CoordinatesPZ90::sinHelpB(int steps) {
    return pow(sin(getGeodeticLatitudeB()), steps);
}

double CoordinatesPZ90::powHelpL2() const {
    return pow (geoDistL, 2);
}

void CoordinatesPZ90::geodeticToRectangular() {
    geoB = getGeodeticLatitudeB(); //перевод широты для удобства переноса формулы (B)
    geoL = getGeodeticLongitudeL() * 180 / M_PI; //перевод долготы для удобства (L)
    geoZoneN = static_cast<int>((6.0 + geoL) / 6.0); //номер шести градусной зоны (n)
    geoDistL = (geoL - (3.0 + 6.0 * (geoZoneN - 1.0))) / 57.29577951; //расстояние от определённой точки до осевого меридиана зоны(l)
    geoAnswX = 6367558.4968 * geoB - sin (2 * geoB) * (16002.8900 + 66.9607 * sinHelpB(2) + 0.3515 * sinHelpB(4)
            - powHelpL2() * (1594561.25 + 5336.535 * sinHelpB(2) + 26.790 * sinHelpB(4) + 0.149 * sinHelpB(6)
            + powHelpL2() * (672483.4 - 811219.9 * sinHelpB(2) + 5420.0 * sinHelpB(4) - 10.6 * sinHelpB(6)
            + powHelpL2() * (278194.0 - 830174.0 * sinHelpB(2) + 572434.0 * sinHelpB(4) - 16010.0 * sinHelpB(6)
            + powHelpL2() * (109500.0 - 574700.0 * sinHelpB(2) + 863700.0 * sinHelpB(4) - 398600.0 * sinHelpB(6))))));
    //формул для нахождения X абсциссы прямоугольных координат
    geoAnswY = (5.0 + 10.0 * geoZoneN) * pow(10, 5) + geoDistL * cos(geoB) * (6378245.0 + 21346.1415 * sinHelpB(2) + 107.1590 *
            sinHelpB(4) + 0.5977 * sinHelpB(6) + pow (geoDistL, 2) * (1070204.16 - 2136826.66 * sinHelpB(2) + 17.98 *
            sinHelpB(4) - 11.99 * sinHelpB(6) + pow (geoDistL, 2) * (270806.0 - 1523417.0 * sinHelpB(2) + 1327645.0 *
            sinHelpB(4) - 21701.0 * sinHelpB(6) + pow (geoDistL, 2) * (79690.0 - 866190.0 * sinHelpB(2) + 1730360.0 *
            sinHelpB(4) - 945460.0 * sinHelpB(6)))));
    //формула для нахождения Y ординаты прямоугольных координат

    setRectangularCoordinates(geoAnswX, geoAnswY);
}

void CoordinatesPZ90::rectangularToGeodetic() {
    rectHelpBeta = getRectangularX() / 6367558.4968; //вспомогательное величина бета
    rectZoneN = static_cast<int>(getRectangularY() / 1000000.0); //номер шести градусной зоны (n)
    rectHelpB0 = rectHelpBeta + sin(2 * rectHelpBeta) * (0.00252588685 - 0.0000149186
            * pow((sin(rectHelpBeta)), 2) + 0.00000011904 * pow((sin(rectHelpBeta)), 4));
    //геодезическая широта точки, абсцисса которой равна х, а ордината равна 0
    rectHelpZ = (getRectangularY() - (10 * rectZoneN + 5) * pow(10, 5)) / (6378245 * cos(rectHelpB0));
    //вспомогательная величина
    rectDeltaB = -1 * pow(rectHelpZ, 2) * sin(2 * rectHelpB0) * (0.251684631 - 0.003369263 * pow(sin(rectHelpB0), 2) + 0.00001127 * pow(sin(rectHelpB0), 4)
            - pow(rectHelpZ, 2) * (0.10500614 - 0.04559916 * pow(sin(rectHelpB0), 2) + 0.00228901 * pow(sin(rectHelpB0), 4) - 0.00002987 * pow(sin(rectHelpB0), 6)
            - pow(rectHelpZ, 2) * (0.042858 - 0.025318 * pow(sin(rectHelpB0), 2) + 0.014346 * pow(sin(rectHelpB0), 4) - 0.001264 * pow(sin(rectHelpB0), 6)
            - pow(rectHelpZ, 2) * (0.01672 - 0.00630 * pow(sin(rectHelpB0), 2) + 0.01188 * pow(sin(rectHelpB0), 4) - 0.00328 * pow(sin(rectHelpB0), 6)))));
    //вспомогательная величина
    rectDistL = rectHelpZ * (1 - 0.0033467108 * pow(sin(rectHelpB0), 2) - 0.0000056002 * pow(sin(rectHelpB0), 4) - 0.0000000187 * pow(sin(rectHelpB0), 6)
            - pow(rectHelpZ, 2) * (0.16778975 + 0.16273586 * pow(sin(rectHelpB0), 2) - 0.00052490 * pow(sin(rectHelpB0), 4) - 0.00000846 * pow(sin(rectHelpB0), 6)
            - pow(rectHelpZ, 2) * (0.0420025 + 0.1487407 * pow(sin(rectHelpB0), 2) + 0.0059420 * pow(sin(rectHelpB0), 4) - 0.0000150 * pow(sin(rectHelpB0), 6)
            - pow(rectHelpZ, 2) * (0.01225 + 0.09477 * pow(sin(rectHelpB0), 2) + 0.03282 * pow(sin(rectHelpB0), 4) - 0.00034 * pow(sin(rectHelpB0), 6)
            - pow(rectHelpZ, 2) * (0.0038 + 0.0524 * pow(sin(rectHelpB0), 2) + 0.0482 * pow(sin(rectHelpB0), 4) - 0.0032 * pow(sin(rectHelpB0), 6))))));
    rectAnswB = rectDeltaB + rectHelpB0; //геодезическая широта
    rectAnswL = 6 * (static_cast<double>(rectZoneN) - 0.5) / 57.29577951 + rectDistL; //геодезическая долгота

    setGeodeticCoordinates(rectAnswB, rectAnswL);
}

void CoordinatesPZ90::getMemberFromGeodeticVector(int vectorMember) {
    if (vectorGeodeticLatitudePZ90->empty() || vectorGeodeticLongitudePZ90->empty()){
        std::cout << "vector is empty!" << std::endl;
    }
    else{
        setGeodeticCoordinates(vectorGeodeticLatitudePZ90->at(vectorMember),
                               vectorGeodeticLongitudePZ90->at(vectorMember));
    }
}

void CoordinatesPZ90::getMemberFromRectangularVector(int vectorMember) {
    if (vectorRectangularXPZ90->empty() || vectorRectangularYPZ90->empty()){
        std::cout << "vector is empty!" << std::endl;
    }
    else{
        setRectangularCoordinates(vectorRectangularXPZ90->at(vectorMember),
                                  vectorRectangularYPZ90->at(vectorMember));
    }
}

void CoordinatesPZ90::loadGeodeticToVector() {
    vectorGeodeticLatitudePZ90->push_back(getGeodeticLatitudeB());
    vectorGeodeticLongitudePZ90->push_back(getGeodeticLongitudeL());
}

void CoordinatesPZ90::loadRectangularToVector() {
    vectorRectangularXPZ90->push_back(getRectangularX());
    vectorRectangularYPZ90->push_back(getRectangularY());
}

void CoordinatesPZ90::fromGeodeticToRectangularVector() {
    if (vectorGeodeticLatitudePZ90->size() == vectorGeodeticLongitudePZ90->size()){
        for (int i = 0; i < vectorGeodeticLatitudePZ90->size(); i++){
            getMemberFromGeodeticVector(i);
            geodeticToRectangular();
            loadRectangularToVector();
        }
    }
    else {
        std::cout << "found difference between latitude and longitude vector!" << std::endl;
    }
}

void CoordinatesPZ90::fromRectangularToGeodeticVector() {
    if (vectorRectangularXPZ90->size() == vectorRectangularYPZ90->size()){
        for (int i = 0; i < vectorRectangularXPZ90->size(); i++){
            getMemberFromRectangularVector(i);
            rectangularToGeodetic();
            loadGeodeticToVector();
        }
    }
    else {
        std::cout << "found difference between latitude and longitude vector!" << std::endl;
    }
}

int CoordinatesPZ90::getSemiMajorAxisConst() {
    return SEMI_MAJOR_AXIS_CONST;
}

double CoordinatesPZ90::getCompressionConst() {
    return COMPRESSION_CONST;
}

double CoordinatesPZ90::getGeodeticHeightH() {
    return geodeticHeightH;
}

CoordinatesPZ90::~CoordinatesPZ90() = default;

CoordinatesPZ90::CoordinatesPZ90() = default;
