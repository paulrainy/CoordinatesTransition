//
// Created by paul on 02.08.23.
//
#include "CoordinatesInterface.h"

#ifndef COORDINATESEX_COORDINATESTRANSITION_H
#define COORDINATESEX_COORDINATESTRANSITION_H


class CoordinatesTransition : protected CoordinatesInterface {
private:

public:
    double get_pz90_latitude();

    double get_pz90_longitude();

    double get_sk42_X();

    double get_sk42_Y();

    void set_pz90(double, double);

    void set_sk42(double, double);

    void pz90_to_sk42();

    double sin_pz90_B(int);
};


#endif //COORDINATESEX_COORDINATESTRANSITION_H