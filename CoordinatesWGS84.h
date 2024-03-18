//
// Created by paul on 3/6/24.
//

#ifndef COORDINATESEX_COORDINATESWGS84_H
#define COORDINATESEX_COORDINATESWGS84_H

#include "CoordinatesInterface.h"

class CoordinatesWGS84 : protected CoordinatesInterface {
private:
    const double GEOCENTRIC_GRAVITATIONAL_CONST = 398600.5; //Геоцентрическая гравитационная постоянная Земли (с учетом атмосферы) (fM)
    const int SEMI_MAJOR_AXIS_CONST = 6378137; //Большая полуось
    const double ANGULAR_VELOCITY_CONST = 7.292115 * pow(10, -5); //Угловая скорость вращения Земли
    const double COMPRESSION_CONST = 1.0 / 298.257223563; //Сжатие общеземного эллипсоида

    double geodeticLatitudeB{};
    double geodeticLongitudeL{};

    //вектор, содержащий набор геодезических широт
    std::vector<double> * vectorGeodeticLatitudeWGS84 = new std::vector<double>;
    //вектор, содержащий набор геодезических долгот
    std::vector<double> * vectorGeodeticLongitudeWGS84 = new std::vector<double>;

    void getMemberFromGeodeticVector(int) override;

    void __attribute__((unused)) getMemberFromRectangularVector(int) override;

    void __attribute__((unused)) setRectangularCoordinates(double, double) override;

    double __attribute__((unused)) getRectangularX() override;
    double __attribute__((unused)) getRectangularY() override;

    void __attribute__((unused)) geodeticToRectangular() override;
    void __attribute__((unused)) rectangularToGeodetic() override;

    void __attribute__((unused)) loadRectangularToVector() override;

    void __attribute__((unused)) fromGeodeticToRectangularVector() override;
    void __attribute__((unused)) fromRectangularToGeodeticVector() override;

public:
    CoordinatesWGS84();
    ~CoordinatesWGS84();

    int getSemiMajorAxisConst() override;
    double getCompressionConst() override;

    double getGeodeticLatitudeB() override;
    double getGeodeticLongitudeL() override;

    void setGeodeticCoordinates(double, double) override;

    void loadGeodeticToVector() override;
};


#endif //COORDINATESEX_COORDINATESWGS84_H
