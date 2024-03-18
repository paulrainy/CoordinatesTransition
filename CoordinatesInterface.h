//
// Created by paul on 02.08.23.
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

#ifndef COORDINATESEX_COORDINATESINTERFACE_H
#define COORDINATESEX_COORDINATESINTERFACE_H

#include <cmath>
#include <vector>
#include <utility>
#include <iostream>

#include <gtest/gtest.h>

class CoordinatesInterface {
protected:
    virtual int getSemiMajorAxisConst() = 0; //геттер для большой полуоси
    virtual double getCompressionConst() = 0; //геттер для сжатия общеземного эллипсоида

    virtual double getGeodeticLatitudeB() = 0; //геттер геодезической широты
    virtual double getGeodeticLongitudeL() = 0; //геттер геодезической долготы
    virtual double getRectangularX() = 0; //геттер прямоугольного X
    virtual double getRectangularY() = 0; //геттер прямоугольного Y

    virtual void setGeodeticCoordinates(double, double) = 0; //сеттер для геодезических координат
    virtual void setRectangularCoordinates(double, double) = 0; //сеттер для прямоугольных координат

    virtual void getMemberFromGeodeticVector(int) = 0; //записывает элемент вектора для удобства
    virtual void getMemberFromRectangularVector(int) = 0; //записывает элемент вектора для удобства

    virtual void loadGeodeticToVector() = 0; //загрузка данных в векторы геодезических пз90
    virtual void loadRectangularToVector() = 0; //загрузка данных в векторы плоских прямоугольных пз90

    virtual void geodeticToRectangular() = 0; //преобразование географических в плоские
    virtual void rectangularToGeodetic() = 0; //преобразование плоских в графические

    virtual void fromGeodeticToRectangularVector() = 0; //преобразование вектора географических в плоские
    virtual void fromRectangularToGeodeticVector() = 0; //преобразование вектора плоских в географические
};

#endif //COORDINATESEX_COORDINATESINTERFACE_H