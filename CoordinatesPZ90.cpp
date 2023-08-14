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

void CoordinatesPZ90::checkGeodeticNum(double testNum1, double testNum2) {
    try {
        if (testNum1 < (-1.0 * M_PI / 2.0) || testNum1 > (M_PI / 2.0)) throw std::string{"wrong latitude!"};
        if (testNum2 < (-180) || testNum2 > 180) throw std::string{"wrong longitude!"};
    }
    catch (std::string errorMessage){
        std::cout << "wrong latitude or longitude!" << std::endl;
        delete[] this;
    }
}

void CoordinatesPZ90::setGeodeticCoordinates(double inputLatitudeB, double inputLongitudeL) {
    checkGeodeticNum(inputLatitudeB, inputLongitudeL);
    //latitudeB = latitudeB * (PI / 180.0);
    this->geodeticLatitudeB = inputLatitudeB;
    this->geodeticLongitudeL = inputLongitudeL;
}

void CoordinatesPZ90::setRectangularCoordinates(double rectangular_X, double rectangular_Y) {
    this->rectangularX = rectangular_X;
    this->rectangularY = rectangular_Y;
}

double CoordinatesPZ90::sinHelpB(int steps) {
    return pow(sin(getGeodeticLatitudeB()), steps);
}

double CoordinatesPZ90::powHelpL2() const {
    return pow (geoDistL, 2);
}

void CoordinatesPZ90::geodeticToRectangular() {
    geoB = getGeodeticLatitudeB(); //перевод широты для удобства переноса формулы (B)
    geoL = getGeodeticLongitudeL(); //перевод долготы для удобства (L)
    geoZoneN = static_cast<int>((6.0 + geoL) / 6.0); //номер шестиградусной зоны (n)
    geoDistL = (geoL - (3.0 + 6.0 * (geoZoneN - 1.0))) / 57.29577951; //расстояние от определёной точки до осевого меридиана зоны(l)
    geoAnswX = 6367558.4968 * geoB - sin (2 * geoB) * (16002.8900 + 66.9607 * sinHelpB(2) + 0.3515 * sinHelpB(4)
            - powHelpL2() * (1594561.25 + 5336.535 * sinHelpB(2) + 26.790 * sinHelpB(4) + 0.149 * sinHelpB(6)
            + powHelpL2() * (672483.4 - 811219.9 * sinHelpB(2) + 5420.0 * sinHelpB(4) - 10.6 * sinHelpB(6)
            + powHelpL2() * (278194.0 - 830174.0 * sinHelpB(2) + 572434.0 * sinHelpB(4) - 16010.0 * sinHelpB(6)
            + powHelpL2() * (109500.0 - 574700.0 * sinHelpB(2) + 863700.0 * sinHelpB(4) - 398600.0 * sinHelpB(6))))));
            //формуля для нахождения X абсциссы прямоугольных координат
    geoAnswY = (5.0 + 10.0 * geoZoneN) * pow(10, 5) + geoDistL * cos(geoB) * (6378245.0 + 21346.1415 * sinHelpB(2) + 107.1590 *
            sinHelpB(4) + 0.5977 * sinHelpB(6) + pow (geoDistL, 2) * (1070204.16 - 2136826.66 * sinHelpB(2) + 17.98 *
            sinHelpB(4) - 11.99 * sinHelpB(6) + pow (geoDistL, 2) * (270806.0 - 1523417.0 * sinHelpB(2) + 1327645.0 *
            sinHelpB(4) - 21701.0 * sinHelpB(6) + pow (geoDistL, 2) * (79690.0 - 866190.0 * sinHelpB(2) + 1730360.0 *
            sinHelpB(4) - 945460.0 * sinHelpB(6)))));
            //формула для нахождения Y ординаты прямоугольных координат

    setRectangularCoordinates(geoAnswX, geoAnswY);
}

void CoordinatesPZ90::rectangularToGeodetic() {
    rectHelpBeta = getRectangularX() / 6367558.4968; //вспомогательное величинв бета
    rectZoneN = static_cast<int>(getRectangularY() * pow(10, -6)); //номер шестиградусной зоны (n)
    rectHelpB0 = rectHelpBeta + sin(2 * rectHelpBeta) * (0.00252588685 - 0.00001491860
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
