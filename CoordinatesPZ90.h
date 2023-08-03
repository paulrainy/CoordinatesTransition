//
// Created by paul on 03.08.23.
//

//  Греческий алфавит
//  A 	α 	alpha 	    альфа
//  B 	β 	beta 	    бета
//  Г 	γ 	gamma 	    гамма
//  Δ 	δ 	delta 	    дельта
//  E 	ε 	epsilon     эпсилон
//  Z 	ζ 	zeta 	    дзета
//  H 	η 	eta 	    эта
//  Θ 	θ 	theta 	    тета
//  I 	ί 	iota 	    йота
//  K 	κ 	kappa 	    каппа
//  Λ 	λ 	lambda 	    ламбда
//  M 	 	mu 	        мю
//  N 	 	nu 	        ню
//  Ξ 	ξ 	xi 	        кси
//  O 	o 	omicron 	омикрон
//  П 	π 	pi 	        пи
//  P 	ρ 	rho 	    ро
//  Σ 	σ 	sigma 	    сигма
//  T 	τ 	tau 	    тау
//  υ 	    upsilon 	ипсилон
//  Ф 	φ 	phi 	 	фи
//  Х 	χ 	chi 	    хи
//  Ψ 	ψ 	psi 	    пси
//  Ω 	ω 	omega 	    омега

#ifndef COORDINATESEX_COORDINATESPZ90_H
#define COORDINATESEX_COORDINATESPZ90_H

#include "CoordinatesInterface.h"

class CoordinatesPZ90 : protected CoordinatesInterface{
private:
    const double GEOCENTRIC_GRAVITATIONAL_CONST = 398600.4418;
    //Геоцентрическая гравитационная постоянная Земли (с учетом атмосферы) (fM)
    const double ANGULAR_VELOCITY_CONST = 7.292115 * pow(10, -5);
    //Угловая скорость вращения Земли
    const double MAJOR_AXIS_CONST = 6378136;
    //Большая полуось
    const double COMPRESSION_CONST = 1.0 / 298.25784;

};


#endif //COORDINATESEX_COORDINATESPZ90_H
