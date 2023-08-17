//
// Created by paul on 10.08.23.
//

#include "CoordinatesFacade.h"

void CoordinatesFacade::objectCreatorGeodeticPZ90(double inputLatitudeB, double inputLongitudeL) {
    auto * objectGeodeticPZ90 = new CoordinatesPZ90;
    objectGeodeticPZ90->setGeodeticCoordinates(inputLatitudeB, inputLongitudeL);
    vectorGeodeticPZ90->push_back(*objectGeodeticPZ90);
}

void CoordinatesFacade::objectCreatorRectangularPZ90(double inputRectangularX, double inputRectangularY) {
    auto * objectRectangularPZ90 = new CoordinatesPZ90;
    objectRectangularPZ90->setRectangularCoordinates(inputRectangularX, inputRectangularY);
    vectorRectangularPZ90->push_back(*objectRectangularPZ90);
}

void CoordinatesFacade::objectCreatorSK42(double inputRectangularX, double inputRectangularY) {
    auto * objectSK42 = new CoordinatesSK42;
    objectSK42->setRectangularCoordinates(inputRectangularX, inputRectangularY);
    vectorSK42->push_back(*objectSK42);
}

void CoordinatesFacade::vectorGeodeticToRectangular() {
    for (int i = 0; i < vectorGeodeticPZ90->size(); i++){
        vectorGeodeticPZ90->at(i).geodeticToRectangular();
        vectorRectangularPZ90->push_back(vectorGeodeticPZ90->at(i));
    }
}

void CoordinatesFacade::vectorRectangularToGeodetic() {

}
