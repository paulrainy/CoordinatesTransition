//
// Created by paul on 29.11.23.
//

#ifndef COORDINATESEX_COORDINATESTRANSLATION_H
#define COORDINATESEX_COORDINATESTRANSLATION_H

#include "CoordinatesPZ90.h"
#include "CoordinatesSK42.h"

class CoordinatesTranslation {
private:
    CoordinatesPZ90 coordinateObjectPZ90;
    CoordinatesSK42 coordinateObjectSK42;
    double coordinateObjectWGS84;

public:
    CoordinatesSK42 PZ90toSK42();
    CoordinatesPZ90 SK42toPZ90();
    double PZ90toWGS84();
};


#endif //COORDINATESEX_COORDINATESTRANSLATION_H
