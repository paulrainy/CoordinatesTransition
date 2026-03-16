//
// Created by paul on 29.11.23.
//

#ifndef COORDINATESEX_COORDINATESTRANSLATION_H
#define COORDINATESEX_COORDINATESTRANSLATION_H

#include "CoordinatesPZ90.h"
#include "CoordinatesSK42.h"
#include "CoordinatesWGS84.h"

class CoordinatesTranslation {
private:
    //объекты классов координат
    CoordinatesPZ90 coordinateObjectPZ90;
    CoordinatesSK42 coordinateObjectSK42;
    CoordinatesWGS84 coordinateObjectWGS84;

    //поля для временного хранения пространственных координат
    double tempSpatialX{};
    double tempSpatialY{};
    double tempSpatialZ{};

    //поля для временного хранения геодезических координат
    double tempGeodeticLatitudeB{};
    double tempGeodeticLongitudeL{};
    double tempGeodeticHeightH{};

    //поля для временного хранения коэффициентов phi
    double phiX{};
    double phiY{};
    double phiZ{};

    //поля для временного хранения коэффициентов delta
    double deltaX{};
    double deltaY{};
    double deltaZ{};

    //методы перевода координат
    void geodeticToSpatial(int, double, double, double, double);
    void spacialToGeodetic(int, double, double, double, double);

    //вспомогательные методы для работы с матрицами
    std::vector<std::vector<double>> getCoeffMatrix(double, double, double, bool);
    std::vector<double> multiplyMatrix(std::vector<std::vector<double>>, std::vector<double>);

public:
    void setCoordinateObjectPZ90(double, double, bool);
    void setCoordinateObjectSK42(double, double);
    void setCoordinateObjectWGS84(double, double);

    CoordinatesPZ90 getCoordinateObjectPZ90();
    CoordinatesSK42 getCoordinateObjectSK42();
    CoordinatesWGS84 getCoordinateObjectWGS84();

    void PZ90toSK42();
    void WGS84toSK42();
    void SK42toPZ90();
    void WGS84toPZ90();
    void PZ90toWGS84();
    void SK42toWGS84();
};


#endif //COORDINATESEX_COORDINATESTRANSLATION_H
