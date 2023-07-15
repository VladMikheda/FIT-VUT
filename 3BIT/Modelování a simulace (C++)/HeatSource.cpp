/**
 * Project: Model vytapeni (Teplarenstvi)
 *
 * File:     HeatSource.cpp
 * Subject:  IMS 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 * @author:  Vladislav Khrisanov xkhris00
 */
#include "HeatSource.h"

double HeatSource::energyConsumption() const {
    if(on){
        return waterFlowRateM * heatCapacityWater * (waterOutT - waterInT);
    }else{
        return 0;
    }

}
