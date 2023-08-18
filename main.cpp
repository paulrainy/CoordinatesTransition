#include <iostream>

#include "CoordinatesFacade.h"

int main() {
    auto * test_object = new CoordinatesPZ90;
    auto * test_object2 = new CoordinatesPZ90;
    std::cout << "Pi: " << M_PI << std::endl;
    test_object->setGeodeticCoordinates(42 * M_PI / 180, 32 * M_PI / 180);
    std::cout << "In radians: " << "(" << test_object->getGeodeticLatitudeB() << ", " << test_object->getGeodeticLongitudeL() * M_PI / 180 << ")" << std::endl;
    std::cout << "In degrees: " << "(" << test_object->getGeodeticLatitudeB() * 180 / M_PI << ", " << test_object->getGeodeticLongitudeL() << ")" << std::endl;
    test_object->geodeticToRectangular();
    std::cout << "Rectangular in m: "<< "(" << test_object->getRectangularX() << ", " << test_object->getRectangularY() << ")" << std::endl;
    std::cout << "Rectangular in km: "<< "(" << test_object->getRectangularX() / 1000 << ", " << test_object->getRectangularY() / 1000 << ")" << std::endl;
    test_object->rectangularToGeodetic();
    std::cout << "In radians again: " << "(" << test_object->getGeodeticLatitudeB() << ", " << test_object->getGeodeticLongitudeL() * M_PI / 180 << ")" << std::endl;

    std::cout << "/////////////////////////////////" << std::endl;

    test_object2->setRectangularCoordinates(5973 * 1000, 722 * 1000);
    std::cout << "Rectangular in m: " << "(" << test_object2->getRectangularX() << ", " << test_object2->getRectangularY() << ")" << std::endl;
    test_object2->rectangularToGeodetic();
    std::cout << "In radians: " << "(" << test_object2->getGeodeticLatitudeB() << ", " << test_object2->getGeodeticLongitudeL() << ")" << std::endl;
    std::cout << "In degrees: " << "(" << test_object2->getGeodeticLatitudeB() * 180 / M_PI << ", " << test_object2->getGeodeticLongitudeL() * 180 / M_PI << ")" << std::endl;
    test_object2->geodeticToRectangular();
    std::cout << "Rectangular in m: "<< "(" << test_object2->getRectangularX() << ", " << test_object2->getRectangularY() << ")" << std::endl;
    std::cout << "Rectangular in km: "<< "(" << test_object2->getRectangularX() / 1000 << ", " << test_object2->getRectangularY() / 1000 << ")" << std::endl;
//    test_object->set_sk42(1000000, 1000000);
////    std::cout << test_object->get_pz90_latitude() << std::endl;
////    std::cout << test_object->get_pz90_longitude() << std::endl;
////    test_object->pz90_to_sk42();
//    std::cout << test_object->get_sk42_X() << std::endl;
//    std::cout << test_object->get_sk42_Y() << std::endl;
//    test_object->sk42_to_pz90();
//    std::cout << test_object->get_pz90_latitude() << std::endl;
//    std::cout << test_object->get_pz90_longitude() << std::endl;
//    test_object->pz90_to_sk42();
//    std::cout << test_object->get_sk42_X() << std::endl;
//    std::cout << test_object->get_sk42_Y() << std::endl;
    return 0;
}
