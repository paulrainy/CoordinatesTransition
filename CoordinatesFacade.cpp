//
// Created by paul on 10.08.23.
//
//
//#include "CoordinatesFacade.h"
//
//void CoordinatesFacade::objectCreatorGeodeticPZ90(double inputLatitudeB, double inputLongitudeL) {
//    auto * objectGeodeticPZ90 = new CoordinatesPZ90;
//    objectGeodeticPZ90->setGeodeticCoordinates(inputLatitudeB, inputLongitudeL);
//    vectorGeodeticPZ90->push_back(*objectGeodeticPZ90);
//}
//
//void CoordinatesFacade::objectCreatorRectangularPZ90(double inputRectangularX, double inputRectangularY) {
//    auto * objectRectangularPZ90 = new CoordinatesPZ90;
//    objectRectangularPZ90->setRectangularCoordinates(inputRectangularX, inputRectangularY);
//    vectorRectangularPZ90->push_back(*objectRectangularPZ90);
//}
//
//void CoordinatesFacade::objectCreatorSK42(double inputRectangularX, double inputRectangularY) {
//    auto * objectSK42 = new CoordinatesSK42;
//    objectSK42->setRectangularCoordinates(inputRectangularX, inputRectangularY);
//    vectorSK42->push_back(*objectSK42);
//}
//
//void CoordinatesFacade::vectorGeodeticToRectangular() {
//    for (auto & i : *vectorGeodeticPZ90){
//        i.geodeticToRectangular();
//        vectorRectangularPZ90->push_back(i);
//    }
////    for (int i = 0; i < vectorGeodeticPZ90->size(); i++){
////        vectorGeodeticPZ90->at(i).geodeticToRectangular();
////        vectorRectangularPZ90->push_back(vectorGeodeticPZ90->at(i));
////    }
//}
//
//void CoordinatesFacade::vectorRectangularToGeodetic() {
//    for (auto & i : *vectorRectangularPZ90){
//        i.rectangularToGeodetic();
//        vectorGeodeticPZ90->push_back(i);
//    }
//}
//
//CoordinatesPZ90 CoordinatesFacade::getMemberVectorGeodeticPZ90(int member) {
//    try{
//        std::string errorMessage;
//        if (member < 0 || member > vectorGeodeticPZ90->size()){
//            errorMessage = "wrong num of member in vector";
//            throw errorMessage;
//        }
//        else {
//            return vectorGeodeticPZ90->at(member);
//        }
//    }
//    catch (std::string errorMessage){
////        CoordinatesPZ90 * nullObject = nullptr;
////        return *nullObject;
//        std::cout << errorMessage << std::endl;
//        delete [] this;
//    }
//
//}
//
//CoordinatesPZ90 CoordinatesFacade::getMemberVectorRectangularPZ90(int member) {
//    try {
//        std::string errorMessage;
//        if (member < 0 || member > vectorRectangularPZ90->size()){
//            errorMessage = "wrong num of member in vector";
//            throw errorMessage;
//        }
//        else {
//            return vectorRectangularPZ90->at(member);
//        }
//    }
//    catch (std::string errorMessage){
//        std::cout << errorMessage << std::endl;
//        delete [] this;
//    }
//}
//
//CoordinatesSK42 CoordinatesFacade::getMemberVectorSK42(int member) {
//    try {
//        std::string errorMessage;
//        if (member < 0 || member > vectorSK42->size()){
//            errorMessage = "wrong num of member in vector";
//            throw errorMessage;
//        }
//        else {
//            return vectorSK42->at(member);
//        }
//    }
//    catch (std::string errorMessage){
////        CoordinatesSK42 * nullObject = nullptr;
////        return *nullObject;
//        std::cout << errorMessage << std::endl;
//        delete [] this;
//    }
//
//}
//
//



