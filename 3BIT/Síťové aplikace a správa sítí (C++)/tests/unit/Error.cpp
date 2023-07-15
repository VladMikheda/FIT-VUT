/**
 * Project: Čtečka novinek ve formátu Atom a RSS s podporou TLS (Tests)
 *
 * File:     Error.cpp
 * Subject:  ISA 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 */

#include "../../Error.h"
/**
 * The test class is used as an injection Errorclass to prevent misbehavior in tests
 */
void Error::errorPrint(int errorNumber) {
    switch (errorNumber) {
        default:
            break;
    }
}

void Error::printMessage(std::string message) {
    bool log = false;
    if(log){
        std::cerr << message << std::endl;
    }
}

void Error::exitProgram(int exitNumber) {
    bool log = false;
    if(log){
        std::cerr << exitNumber << std::endl;
    }
}

void Error::helpOut() {
    bool log = false;
    if(log){
        std::cerr << "help" << std::endl;
    }
}

