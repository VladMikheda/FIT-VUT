/**
 * Project: Model vytapeni (Teplarenstvi)
 *
 * File:     IRoom.h
 * Subject:  IMS 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 * @author:  Vladislav Khrisanov xkhris00
 */

#ifndef MODEL_IROOM_H
#define MODEL_IROOM_H
#include <iostream>

class IRoom{
public:
    int mode;
    std::string name;
    //house parameters
    double height;
    double length;
    double width;
    double t;
    double tMax;

    //window parameters
    double heightWindow;
    double widthWindow;
    double windowS() const;
    const double windowR =  0.38;

    //wall parameters
    virtual double wallInS() const = 0;
    virtual double wallOutS() const = 0;
    virtual double roofOutS() const = 0;
    double wallHeatConductivity;
    double wallOutThickness; //m
    double wallInThickness; //m
    virtual double allRoofOutR() const = 0;
    virtual double allInR() const = 0;
    virtual double allOutR() const = 0;

    //air
    const double airP = 1.2754;
    double m() const;
        // Для нагрева 1кг воздуха на 1градус нужно 1000Дж
    double airThermCond() const;


    //heater
//    const int heatCapacityWater = 4200;
    const double heatCapacityMaterial = 9.1;
    const double heatWallThickness = 0.005;
    const double densityMaterial = 7000;
//    double heaterConductivity;
    int countSection;
    double heartsWaterInT = 15;
    double heartsWaterOutT = 15;
//    double heartsSurface = 15;
    double heaterS() const;
    double heaterL() const;

    bool inSystem = true;

//    virtual ~IRoom(){};
};


#endif //MODEL_IROOM_H
