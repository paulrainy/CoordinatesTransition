#include <iostream>

#include "CoordinatesPZ90.h"

int main() {
    auto * test_object = new CoordinatesPZ90;
    std::cout << M_PI << std::endl;
    //test_object->setGeodeticCoordinates(42 * M_PI / 180, 32 * M_PI / 180);
    test_object->setGeodeticCoordinates(42 * M_PI / 180 , 32);
    std::cout << "(" << test_object->getGeodeticLatitudeB() << ", " << test_object->getGeodeticLongitudeL() * M_PI / 180 << ")" << std::endl;
    test_object->geodeticToRectangular();
    std::cout << "(" << test_object->getRectangularX() << ", " << test_object->getRectangularY() << ")" << std::endl;
    test_object->rectangularToGeodetic();
    std::cout << "(" << test_object->getGeodeticLatitudeB() << ", " << test_object->getGeodeticLongitudeL() << ")" << std::endl;
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
