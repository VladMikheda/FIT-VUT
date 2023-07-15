/**
 * Project: Model vytapeni (Teplarenstvi)
 *
 * File:     Bedroom.cpp
 * Subject:  IMS 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 * @author:  Vladislav Khrisanov xkhris00
 */

#include "Bedroom.h"

Bedroom::Bedroom(int mode) {
    this->mode = mode;
    this->name = "Bedroom";
    this->height = 3;
    this->length = 7;
    this->width = 2.5;
    this->t = 15;
    this->tMax = 18;

    this->heightWindow = 2;
    this->widthWindow = 1.2;

    this->wallHeatConductivity = 0.87;
    this->wallOutThickness = 0.64;
    this->wallInThickness = 0.25;

    this->countSection = 8;
}

double Bedroom::wallInS() const {
    return length * height + width * height;
}

double Bedroom::wallOutS() const {
    return (length * height + width * height) - this->windowS();
}

double Bedroom::allInR() const {
    return wallInThickness/wallHeatConductivity;
}

double Bedroom::allOutR() const {
//    double basaltWoolConductivity = 0.035;
//    double basaltWoolThickness = 0.15;
//    double styrofoamConductivity = 0.043;
//    double styrofoamWoolThickness = 0.15;

    double rockWoolConductivity = 0.035;
    double rockWoolThickness = 0.20;

    double knaufConductivity = 0.036;
    double knaufThickness = 0.05;

    if(mode == 1){
        return wallOutThickness/wallHeatConductivity + rockWoolThickness/rockWoolConductivity;
    }else if(mode == 2){
        return wallOutThickness/wallHeatConductivity + knaufThickness/knaufConductivity;
    }else{
        return wallOutThickness/wallHeatConductivity;
    }
//    return wallOutThickness/wallHeatConductivity ;//+ styrofoamWoolThickness/styrofoamConductivity;
}


double Bedroom::roofOutS() const {
    return length * width;
}
double Bedroom::allRoofOutR() const {
    double concreteConductivity = 1.6;
    double concreteThickness = 0.25;

    double woodenBoardConductivity = 0.2;
    double woodenBoardThickness = 0.05;

    double sawdustConductivity = 0.09;
    double sawdustThickness = 0.30;


    double rockWoolConductivity = 0.035;
    double rockWoolThickness = 0.30;

    if(mode == 1 || mode == 2){
        return concreteThickness / concreteConductivity + woodenBoardThickness / woodenBoardConductivity + rockWoolThickness / rockWoolConductivity;
    }else{
        return concreteThickness / concreteConductivity + woodenBoardThickness / woodenBoardConductivity + sawdustThickness / sawdustConductivity;
    }
//    return concreteThickness / concreteConductivity + woodenBoardThickness / woodenBoardConductivity + sawdustThickness / sawdustConductivity;
}
