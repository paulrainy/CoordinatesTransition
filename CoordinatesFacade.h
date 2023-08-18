//
// Created by paul on 10.08.23.
//

#ifndef COORDINATESEX_COORDINATESFACADE_H
#define COORDINATESEX_COORDINATESFACADE_H

#include "CoordinatesPZ90.h"
#include "CoordinatesSK42.h"
#include "CoordinatesInterface.h"

#include <vector>
#include <iostream>

class CoordinatesFacade {
private:
    std::vector<CoordinatesPZ90> * vectorGeodeticPZ90 = new std::vector<CoordinatesPZ90>;
    std::vector<CoordinatesPZ90> * vectorRectangularPZ90 = new std::vector<CoordinatesPZ90>;
    std::vector<CoordinatesSK42> * vectorSK42 = new std::vector<CoordinatesSK42>;

public:
    void objectCreatorGeodeticPZ90(double, double);
    void objectCreatorRectangularPZ90(double, double);
    void objectCreatorSK42(double, double);

    void vectorGeodeticToRectangular();
    void vectorRectangularToGeodetic();

    //мб сделать дополнительные методы для создания объектов???


};


#endif //COORDINATESEX_COORDINATESFACADE_H
