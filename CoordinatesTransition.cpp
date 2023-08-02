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

double CoordinatesTransition::sin_pz90_B(int steps) {
    return pow(sin(get_pz90_latitude()), steps);
}

void CoordinatesTransition::pz90_to_sk42() {
    double pz90_B = get_pz90_latitude(); //перевод широты для удобства переноса формулы (B)

    double pz90_L = get_pz90_longitude(); //перевод долготы для удобства (L)

    int pz90_zone_n = static_cast<int>((6 + pz90_L) / 6); //номер шестиградусной зоны (n)

    double pz90_distance_l = (pz90_L - (3 + 6 * (pz90_zone_n - 1))) / 57.29577951; //расстояние от определёной точки до осевого меридиана зоны(l)

    double sk42_answ_X, sk42_answ_Y;

    sk42_answ_X = 6367558.4968 * pz90_B - sin (2 * pz90_B) * (16002.8900 + 66.9607 * sin_pz90_B(2) + 0.3515 * sin_pz90_B(4) -
            pow (pz90_distance_l, 2) * (1594561.25 + 5336.535 * sin_pz90_B(2) + 26.790 * sin_pz90_B(4) + 0.149 * sin_pz90_B(6) +
            pow (pz90_distance_l, 2) * (672483.4 - 811219.9 * sin_pz90_B(2) + 5420.0 * sin_pz90_B(4) - 10.6 * sin_pz90_B(6) +
            pow (pz90_distance_l, 2) * (278194 - 830174 * sin_pz90_B(2) + 572434 * sin_pz90_B(4) - 16010 * sin_pz90_B(6) +
            pow (pz90_distance_l, 2) * (109500 - 574700 * sin_pz90_B(2) + 863700 * sin_pz90_B(4) - 398600 * sin_pz90_B(6))))));
            //формуля для нахождения X абсциссы ск42
    sk42_answ_Y = (5 + 10 * pz90_zone_n) * pow(10, 5) + pz90_distance_l * cos(pz90_B) * (6378245 + 21346.1415 * sin_pz90_B(2) + 107.1590 * sin_pz90_B(4)
            + 0.5977 * sin_pz90_B(6) + pow (pz90_distance_l, 2) * (1070204.16 - 2136826.66 * sin_pz90_B(2) + 17.98 * sin_pz90_B(4)
            - 11.99 * sin_pz90_B(6) + pow (pz90_distance_l, 2) * (270806 - 1523417 * sin_pz90_B(2) + 1327645 * sin_pz90_B(4) - 21701 * sin_pz90_B(6)
            + pow (pz90_distance_l, 2) * (79690 - 866190 * sin_pz90_B(2) + 1730360 * sin_pz90_B(4) - 945460 * sin_pz90_B(6)))));
            //формула для нахождения Y ординаты ск42

    set_sk42(sk42_answ_X, sk42_answ_Y);
}

void CoordinatesTransition::sk42_to_pz90() {
    double sk42_help_beta = get_sk42_X() / 6367558.4968; //вспомогательное величинв бета

    int sk42_zone_n = static_cast<int>(get_sk42_Y() / pow(10, 6)); //номер шестиградусной зоны (n)

    double pz90_help_B0 = sk42_help_beta + sin(2 * sk42_help_beta) * (0.00252588685 - 0.00001491860 * pow((sin(sk42_help_beta)), 2) +
            0.00000011904 * pow((sin(sk42_help_beta)), 4));

    double sk42_help_z = (get_sk42_Y() - (10 * sk42_zone_n + 5) * pow(10, 5)) / (6378245 * cos(pz90_help_B0));


}

void CoordinatesTransition::array_pz90_to_sk42() {

}

void CoordinatesTransition::array_sk42_to_pz90() {

}