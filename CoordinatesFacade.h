//
// Created by paul on 10.08.23.
//

#ifndef COORDINATESEX_COORDINATESFACADE_H
#define COORDINATESEX_COORDINATESFACADE_H

#include "CoordinatesPZ90.h"
#include "CoordinatesSK42.h"
#include "CoordinatesInterface.h"

class CoordinatesFacade {
private:
    CoordinatesPZ90 * objectPZ90 = new CoordinatesPZ90;
    CoordinatesSK42 * objectSK42 = new CoordinatesSK42;
    //мб как-то по-другому??

public:

    void fabricPZ90();
    void fabricSK42();
    //вообще идеи не шли

};


#endif //COORDINATESEX_COORDINATESFACADE_H
