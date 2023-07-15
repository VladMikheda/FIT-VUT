/**
 * Project: Model vytapeni (Teplarenstvi)
 *
 * File:     Bathroom.cpp
 * Subject:  IMS 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 * @author:  Vladislav Khrisanov xkhris00
 */
#include "Bathroom.h"

Bathroom::Bathroom(int mode) {
    this->mode = mode;
    this->name = "Bathroom";
    this->height = 3;
    this->length = 4;
    this->width = 1.5;
    this->t = 15;
    this->tMax = 20;

    this->heightWindow = 0;
    this->widthWindow = 0;

    this->wallHeatConductivity = 0.87;
    this->wallOutThickness = 0.64;
    this->wallInThickness = 0.25;

    this->countSection = 5;
}


double Bathroom::wallInS() const {
    return length * height + width * height;
}


double Bathroom::wallOutS() const {
    return (length * height + width * height) - this->windowS();
}

double Bathroom::allInR() const {
    return wallInThickness/wallHeatConductivity;
}

double Bathroom::allOutR() const {
//    double basaltWoolConductivity = 0.035;
//    double basaltWoolThickness = 0.15;

    double rockWoolConductivity = 0.035;
    double rockWoolThickness = 0.20;

//    return wallOutThickness/wallHeatConductivity ;//+ styrofoamWoolThickness/styrofoamConductivity;


    double knaufConductivity = 0.036;
    double knaufThickness = 0.05;

    if(mode == 1){
        return wallOutThickness/wallHeatConductivity + rockWoolThickness/rockWoolConductivity;
    }else if(mode == 2){
        return wallOutThickness/wallHeatConductivity + knaufThickness/knaufConductivity;
    }else{
        return wallOutThickness/wallHeatConductivity;
    }

}

double Bathroom::roofOutS() const {
    return length * width;
}
double Bathroom::allRoofOutR() const {
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


}

