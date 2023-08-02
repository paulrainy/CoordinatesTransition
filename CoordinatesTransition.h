//
// Created by paul on 02.08.23.
//

#include "CoordinatesInterface.h"

#ifndef COORDINATESEX_COORDINATESTRANSITION_H
#define COORDINATESEX_COORDINATESTRANSITION_H

class CoordinatesTransition : protected CoordinatesInterface {
private:

public:
    double get_pz90_latitude() override;

    double get_pz90_longitude() override;

    double get_sk42_X() override;

    double get_sk42_Y() override;

    void set_pz90(double, double) override;

    void set_sk42(double, double) override;

    void pz90_to_sk42() override;

    double sin_pz90_B(int) override;

    void sk42_to_pz90() override;

    void array_pz90_to_sk42() override;

    void array_sk42_to_pz90() override;
};

#endif //COORDINATESEX_COORDINATESTRANSITION_H