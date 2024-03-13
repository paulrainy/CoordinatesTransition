//
// Created by paul on 29.11.23.
//

#ifndef COORDINATESEX_COORDINATESTRANSLATION_H
#define COORDINATESEX_COORDINATESTRANSLATION_H

#include "CoordinatesPZ90.h"
#include "CoordinatesSK42.h"
#include "CoordinatesWGS84.h"

class CoordinatesTranslation {
private:
    CoordinatesPZ90 coordinateObjectPZ90;
    CoordinatesSK42 coordinateObjectSK42;
    CoordinatesWGS84 coordinateObjectWGS84;

public:
    void setCoordinateObjectPZ90(double, double, bool);
    void setCoordinateObjectSK42(double, double);
    void setCoordinateObjectWGS84(double, double);

    CoordinatesPZ90 getCoordinateObjectPZ90();
    CoordinatesSK42 getCoordinateObjectSK42();
    CoordinatesWGS84 getCoordinateObjectWGS84();

    void PZ90toSK42();
    void WGS84toSK42();
    void SK42toPZ90();
    void WGS84toPZ90();
    void PZ90toWGS84();
    void SK42toWGS84();
};


#endif //COORDINATESEX_COORDINATESTRANSLATION_H
