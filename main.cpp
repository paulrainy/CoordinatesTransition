#include <iostream>

#include "CoordinatesTransition.h"

int main() {
    auto * test_object = new CoordinatesTransition;
    test_object->set_pz90(30.5, 24.5);
    std::cout << test_object->get_pz90_latitude() << std::endl;
    std::cout << test_object->get_pz90_longitude() << std::endl;
    return 0;
}
