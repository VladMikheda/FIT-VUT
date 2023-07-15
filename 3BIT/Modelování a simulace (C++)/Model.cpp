/**
 * Project: Model vytapeni (Teplarenstvi)
 *
 * File:     Model.cpp
 * Subject:  IMS 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 * @author:  Vladislav Khrisanov xkhris00
 */
#include "Model.h"



void Model::start(int timeMax, House& house, HeatSource heatSource, double t) {

    Weather weather(t);
    heatSource.amountRoom = house.amountRoom;
    double averageWaterTOut = 0;
    double amountQ = 0;

    //initialization of lists for collecting statistics
    std::list<double> releasedSourceEnergy;
    std::list<double> energyRadiator;
    std::list<double> energyLoss;
    std::list<double> totalEnergy;
    std::list<double> temperatureHall;
    std::list<double> temperatureKitchen;
    std::list<double> temperatureBathroom;
    std::list<double> temperatureBedroom;

    //main loop
    for(int time = 0; time < timeMax; time++){
        double averageHeatInWalls = 0;
        // for collecting statistics
        double QRadiator = 0.0;
        double QLoss = 0.0;
        double QTotalEnergy = 0.0;

        //If all rooms are off, then the gas boiler is not working
        if(heatSource.amountRoom != 0){
            if(averageWaterTOut != 0){
                heatSource.waterInT = averageWaterTOut / heatSource.amountRoom;
                averageWaterTOut = 0;
            }else{
                heatSource.waterInT = 15;
            }
        }else{
            heatSource.on = false;
        }

        //Energy consumption statistics for water heating
        double outQ = heatSource.energyConsumption();
        releasedSourceEnergy.push_back(outQ);
        amountQ += outQ;

        //Each room passes in turn
        for(IRoom *room : house.rooms){

            //Calculation of how much renewed water
            double addWater = 0;
            if(heatSource.amountRoom != 0){
                addWater = heatSource.waterFlowRate / heatSource.amountRoom;
            }
            //if the room is heated
            if(room->inSystem){
                //find the new temperature in the radiator
                double newWaterInHeart1 = (room->heaterL() - addWater) * room->heartsWaterInT;
                double newWaterInHeart2 = addWater * heatSource.waterOutT;
                double newWaterInHeartAll = newWaterInHeart1 + newWaterInHeart2;
                double newWaterHeartsInT =  newWaterInHeartAll / room->heaterL();
                room->heartsWaterInT = newWaterHeartsInT;

                //Calculation of the temperature of the outgoing water
                // from the radiator according to tabular data
                if(room->heartsWaterInT >= 85){
                    room->heartsWaterOutT = room->heartsWaterInT - 20;
                }else if(room->heartsWaterInT >= 70){
                    room->heartsWaterOutT = room->heartsWaterInT - 16;
                }else if(room->heartsWaterInT >= 50){
                    room->heartsWaterOutT = room->heartsWaterInT - 10;
                }else if(room->heartsWaterInT >= 40){
                    room->heartsWaterOutT = room->heartsWaterInT - 5;
                }else{
                    room->heartsWaterOutT = room->heartsWaterInT;
                }

                //Heat dissipation by radiator
                double QToRoom = room->heatCapacityMaterial * room->heaterS() *
                        ((room->heartsWaterInT + room->heartsWaterOutT) / 2 - room->t);
                QRadiator += QToRoom;

                //Heat loss through walls
                double QOutRoom = heatLoss(room, house, weather);
                QLoss += QOutRoom;

                //The amount of energy entering the room
                double QRoom = QToRoom - QOutRoom;
                QTotalEnergy += QRoom;

                //Heating temperature
                double addRoomT = QRoom / room->airThermCond();
                room->t += addRoomT;

                //Collection of statistics
                if(room->name == "Hall"){
                    temperatureHall.push_back(room->t);
                }else if(room->name == "Kitchen"){
                    temperatureKitchen.push_back(room->t);
                }else if(room->name == "Bathroom"){
                    temperatureBathroom.push_back(room->t);
                }else if(room->name == "Bedroom"){
                    temperatureBedroom.push_back(room->t);
                }

                //If the room is hot then turn it off
                if(room->t >= room->tMax + 2){
                    room->inSystem = false;
                    heatSource.amountRoom--;
                }
            }else{
                double QToRoom = 0;
                //Heat dissipation by radiator and
                //decrease in water temperature in the radiator
                if(room->heartsWaterOutT  > room->t) {
                    room->heartsWaterOutT = room->heartsWaterInT;
                    QToRoom = room->heatCapacityMaterial * room->heaterS() *
                                     ((room->heartsWaterInT + room->heartsWaterOutT) / 2 - room->t);
                    double minusHeatT = QToRoom / (room->heaterL() * 4187);
                    room->heartsWaterInT -= minusHeatT;
                    QRadiator += QToRoom;
                }

                //Heat loss through walls
                double QOutRoom = heatLoss(room, house, weather);
                QLoss += QOutRoom;

                //The amount of energy entering the room
                double QRoom = QToRoom - QOutRoom;
                QTotalEnergy += QRoom;

                //Heating temperature(-/+)
                double addRoomT = QRoom / room->airThermCond();
                room->t += addRoomT;

                //Collection of statistics
                if(room->name == "Hall"){
                    temperatureHall.push_back(room->t);
                }else if(room->name == "Kitchen"){
                    temperatureKitchen.push_back(room->t);
                }else if(room->name == "Bathroom"){
                    temperatureBathroom.push_back(room->t);
                }else if(room->name == "Bedroom"){
                    temperatureBedroom.push_back(room->t);
                }

                //If the room has cooled down, turn on the heating in it.
                if(room->t <= room->tMax - 2){
                    room->inSystem = true;
                    heatSource.amountRoom++;
                }
            }

            averageHeatInWalls += room->t;

            if(heatSource.amountRoom != 0){
                if(room->inSystem){
                    heatSource.on = true;
                    averageWaterTOut += room->heartsWaterOutT;
                }
            }else{
                heatSource.on = false;
            }
        }

        energyRadiator.push_back(QRadiator);
        energyLoss.push_back(QLoss);
        totalEnergy.push_back(QTotalEnergy);

        //Average house temperature
        house.averageHeatInWalls = averageHeatInWalls / house.amountRoom;
    }

    std::cout << "The energy that a gas boiler spends on heating water (W or J/s): " << std::endl;
    outData(releasedSourceEnergy);

    std::cout << "Energy that is emitted by the radiator in all rooms (W or J/s):" << std::endl;
    outData(energyRadiator);

    std::cout << "Energy loss in all rooms (W or J/s):" << std::endl;
    outData(energyLoss);

    std::cout << "The energy that stays in the room (W or J/s):" << std::endl;
    outData(totalEnergy);

    std::cout << "Changes in room temperature in the hall (С):" << std::endl;
    outData(temperatureHall);

    std::cout << "Changes in room temperature in the kitchen (С):" << std::endl;
    outData(temperatureKitchen);

    std::cout << "Changes in room temperature in the bathroom (С):" << std::endl;
    outData(temperatureBathroom);

    std::cout << "Changes in room temperature in the bedroom (С):" << std::endl;
    outData(temperatureBedroom);

    std::cout << "The total amount of energy that was expended by the boiler during the simulation of the part (kW): " << amountQ /1000 << std::endl;
}

double Model::heatLoss(IRoom *room,  House& house,  Weather weather) {

    double QOutWallOutRoom =  (1/room->allOutR()) * (room->t - weather.getWeather()) * room->wallOutS();
    double QOutRoofRoom =  (1/room->allRoofOutR()) * (room->t - weather.getWeather()) * room->roofOutS();
    double QOutWallInRoom =  (1/room->allInR()) * (room->t - house.averageHeatInWalls) * room->wallInS();
    double QOutWindowRoom =  (1/room->windowR) * (room->t - weather.getWeather()) * room->windowS();
    double QOutRoom = QOutWallOutRoom + QOutWallInRoom + QOutWindowRoom + QOutRoofRoom;

    return QOutRoom;
}

void Model::outData(const std::list<double>& data) {
    for(double d : data){
        std::cout << d << ",";
    }
    std::cout << std::endl;
    std::cout << std::endl;
}



