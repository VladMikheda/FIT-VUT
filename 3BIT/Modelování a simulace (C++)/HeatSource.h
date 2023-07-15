/**
 * Project: Model vytapeni (Teplarenstvi)
 *
 * File:     HeatSource.h
 * Subject:  IMS 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 * @author:  Vladislav Khrisanov xkhris00
 */
#ifndef MODEL_HEATSOURCE_H
#define MODEL_HEATSOURCE_H

class HeatSource {

public:

    bool on = true;
    const double waterFlowRateM = 0.000263;//m3/s
    const double waterFlowRate = 0.263;//ls/s
    double waterOutT = 80;
    double waterInT = 15;
    const int heatCapacityWater =  1163;//Wt/m3C
    double energyConsumption() const;
    int amountRoom = 0;

};


#endif //MODEL_HEATSOURCE_H
