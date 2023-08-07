//
// Created by paul on 03.08.23.
//

#include "CoordinatesPZ90.h"

double CoordinatesPZ90::get_geodetic_latitude_B() {
    return geodetic_latitude_B;
}

double CoordinatesPZ90::get_geodetic_longitude_L() {
    return geodetic_longitude_L;
}

double CoordinatesPZ90::get_rectangular_X() {
    return rectangular_X;
}

double CoordinatesPZ90::get_rectangular_Y() {
    return rectangular_Y;
}

void CoordinatesPZ90::set_geodetic_coordinates(double geodetic_latitude_B, double geodetic_longitude_L) {
    this->geodetic_latitude_B = geodetic_latitude_B;
    this->geodetic_longitude_L = geodetic_longitude_L;
}

void CoordinatesPZ90::set_rectangular_coordinates(double rectangular_X, double rectangular_Y) {
    this->rectangular_X = rectangular_X;
    this->rectangular_Y = rectangular_Y;
}

double CoordinatesPZ90::sin_help_B(int steps) {
    return pow(sin(get_geodetic_latitude_B()), steps);
}

void CoordinatesPZ90::geodetic_to_rectangular(double , double) {
    geo_B = get_geodetic_latitude_B(); //перевод широты для удобства переноса формулы (B)
    geo_L = get_geodetic_longitude_L(); //перевод долготы для удобства (L)
    geo_zone_n = static_cast<int>((6 + geo_L) / 6); //номер шестиградусной зоны (n)
    geo_dist_l = (geo_L - (3 + 6 * (geo_zone_n - 1))) / 57.29577951; //расстояние от определёной точки до осевого меридиана зоны(l)
    pz90_answ_X = 6367558.4968 * geo_B - sin (2 * geo_B) * (16002.8900 + 66.9607 * sin_help_B(2) + 0.3515 * sin_help_B(4) -
            pow (geo_dist_l, 2) * (1594561.25 + 5336.535 * sin_help_B(2) + 26.790 * sin_help_B(4) + 0.149 * sin_help_B(6) +
            pow (geo_dist_l, 2) * (672483.4 - 811219.9 * sin_help_B(2) + 5420.0 * sin_help_B(4) - 10.6 * sin_help_B(6) +
            pow (geo_dist_l, 2) * (278194 - 830174 * sin_help_B(2) + 572434 * sin_help_B(4) - 16010 * sin_help_B(6) +
            pow (geo_dist_l, 2) * (109500 - 574700 * sin_help_B(2) + 863700 * sin_help_B(4) - 398600 * sin_help_B(6))))));
            //формуля для нахождения X абсциссы ск42
    pz90_answ_Y = (5 + 10 * geo_zone_n) * pow(10, 5) + geo_dist_l * cos(geo_B) * (6378245 + 21346.1415 * sin_help_B(2) + 107.1590 * sin_help_B(4)
                                                                                  + 0.5977 * sin_help_B(6) + pow (geo_dist_l, 2) * (1070204.16 - 2136826.66 * sin_help_B(2) + 17.98 * sin_help_B(4)
                                                                                                                                    - 11.99 * sin_help_B(6) + pow (geo_dist_l, 2) * (270806 - 1523417 * sin_help_B(2) + 1327645 * sin_help_B(4) - 21701 * sin_help_B(6)
                                                                                                                                                                                     + pow (geo_dist_l, 2) * (79690 - 866190 * sin_help_B(2) + 1730360 * sin_help_B(4) - 945460 * sin_help_B(6)))));
            //формула для нахождения Y ординаты ск42

    set_rectangular_coordinates(pz90_answ_X, pz90_answ_Y);
}

void CoordinatesPZ90::rectangular_to_geodetic(double, double) {

}
