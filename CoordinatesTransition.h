//
// Created by paul on 02.08.23.
//

#include "CoordinatesInterface.h"

#ifndef COORDINATESEX_COORDINATESTRANSITION_H
#define COORDINATESEX_COORDINATESTRANSITION_H

class CoordinatesTransition : protected CoordinatesInterface {
private:
    double pz90_B, pz90_L, pz90_distance_l, pz90_answ_X, pz90_answ_Y;
    int pz90_zone_n, sk42_zone_n;
    double sk42_delta_B, sk42_distance_l, sk42_help_beta, sk42_help_B0, sk42_help_z, sk42_answ_B, sk42_answ_L;

    double sin_pz90_B(int);
    //метод, сокращающий подсчёты синусов широты и долготы в соответствующих формулах перевода из пз90 в ск42

public:
    double get_pz90_latitude() override;

    double get_pz90_longitude() override;

    double get_sk42_X() override;

    double get_sk42_Y() override;

    void set_pz90(double, double) override;

    void set_sk42(double, double) override;

    void pz90_to_sk42() override;

    void sk42_to_pz90() override;

    void array_pz90_to_sk42() override;

    void array_sk42_to_pz90() override;

};

#endif //COORDINATESEX_COORDINATESTRANSITION_H