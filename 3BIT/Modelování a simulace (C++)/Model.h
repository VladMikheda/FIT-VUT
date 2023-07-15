/**
 * Project: Model vytapeni (Teplarenstvi)
 *
 * File:     Model.h
 * Subject:  IMS 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 * @author:  Vladislav Khrisanov xkhris00
 */

#ifndef MODEL_MODEL_H
#define MODEL_MODEL_H


#include "IRoom.h"
#include "House.h"
#include "HeatSource.h"
#include "Weather.h"

class Model {

public:



    void start(int timeMax, House &house, HeatSource heatSours, double t);

private:
    double heatLoss(IRoom *room,  House& house,  Weather weather);
    void outData( const std::list<double>& data);
};


#endif //MODEL_MODEL_H
