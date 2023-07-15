/**
 * Project: Model vytapeni (Teplarenstvi)
 *
 * File:     Kitchen.cpp
 * Subject:  IMS 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 * @author:  Vladislav Khrisanov xkhris00
 */
#include "Kitchen.h"

Kitchen::Kitchen(int mode) {
    this->mode = mode;
    this->name = "Kitchen";
    this->height = 3;
    this->length = 6;
    this->width = 4;
    this->t = 15;
    this->tMax = 18;

    this->heightWindow = 2;
    this->widthWindow = 1.2;

    this->wallHeatConductivity = 0.87;
    this->wallOutThickness = 0.64;
    this->wallInThickness = 0.25;

    this->countSection = 10;
}

double Kitchen::wallInS() const {
    return length * height + width * height;
}

double Kitchen::wallOutS() const {
    return (length * height + width * height) - this->windowS();
}

double Kitchen::allInR() const {
    return wallInThickness/wallHeatConductivity;
}

double Kitchen::allOutR() const {
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

double Kitchen::roofOutS() const {
    return length * width;
}
double Kitchen::allRoofOutR() const {
    double concreteConductivity = 1.6;
    double concreteThickness = 0.25;

    double woodenBoardConductivity = 0.2;
    double woodenBoardThickness = 0.05;

    double sawdustConductivity = 0.09;
    double sawdustThickness = 0.30;


    double rockWoolConductivity = 0.035;
    double rockWoolThickness = 0.30;

    if(mode == 1 || mode == 2 ){
        return concreteThickness / concreteConductivity + woodenBoardThickness / woodenBoardConductivity + rockWoolThickness / rockWoolConductivity;
    }else{
        return concreteThickness / concreteConductivity + woodenBoardThickness / woodenBoardConductivity + sawdustThickness / sawdustConductivity;
    }

//    return concreteThickness / concreteConductivity + woodenBoardThickness / woodenBoardConductivity + sawdustThickness / sawdustConductivity;
}

