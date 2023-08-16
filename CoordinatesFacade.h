//
// Created by paul on 10.08.23.
//

#ifndef COORDINATESEX_COORDINATESFACADE_H
#define COORDINATESEX_COORDINATESFACADE_H

#include "CoordinatesPZ90.h"
#include "CoordinatesSK42.h"
#include "CoordinatesInterface.h"

#include <vector>

class CoordinatesFacade {
private:
    std::vector<CoordinatesPZ90> * vectorGeodeticPZ90 = new std::vector<CoordinatesPZ90>;
    std::vector<CoordinatesPZ90> * vectorRectangularPZ90 = new std::vector<CoordinatesPZ90>;

public:
    void objectCreatorPZ90();

    void objectCreatorSK42();

};


#endif //COORDINATESEX_COORDINATESFACADE_H
