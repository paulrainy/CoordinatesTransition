//
// Created by paul on 02.08.23.
//

#include "CoordinatesTransition.h"

double CoordinatesTransition::get_pz90_latitude() {
    return pz90_latitude;
}

double CoordinatesTransition::get_pz90_longitude() {
    return pz90_longitude;
}

double CoordinatesTransition::get_sk42_X() {
    return sk42_X;
}

double CoordinatesTransition::get_sk42_Y() {
    return sk42_Y;
}

void CoordinatesTransition::set_pz90(double pz90_latitude, double pz90_longitude) {
    this->pz90_latitude = pz90_latitude;
    this->pz90_longitude = pz90_longitude;
}

void CoordinatesTransition::set_sk42(double sk42_X, double sk42_Y) {
    this->sk42_X = sk42_X;
    this->sk42_Y = sk42_Y;
}
