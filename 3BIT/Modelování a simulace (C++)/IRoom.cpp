/**
 * Project: Model vytapeni (Teplarenstvi)
 *
 * File:     IRoom.cpp
 * Subject:  IMS 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 * @author:  Vladislav Khrisanov xkhris00
 */
#include "IRoom.h"

double IRoom::windowS() const {
    return  heightWindow * widthWindow;
}

//double IRoom::wallS() const {
//    return (length * width + length * height) - this->windowS();
//}

//double IRoom::wallR() const {
//    return wallThickness / wallHeatConductivity;
//}

double IRoom::m() const {
    return (height * length * width) * airP;
}

double IRoom::airThermCond() const {
    return this->m() * 1000;
}

double IRoom::heaterS() const {
    double oneSectionS = 0.244; //m
    return countSection * oneSectionS;
}

double IRoom::heaterL() const {
    double litersInSection = 1;
    return countSection * litersInSection;
}
