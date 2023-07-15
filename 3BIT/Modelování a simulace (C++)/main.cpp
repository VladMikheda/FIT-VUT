/**
 * Project: Model vytapeni (Teplarenstvi)
 *
 * File:     main.cpp
 * Subject:  IMS 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 * @author:  Vladislav Khrisanov xkhris00
 */

#include <iostream>
#include<cmath>
#include <cstring>
#include "Hall.h"
#include "Model.h"
#include "Bathroom.h"
#include "Bedroom.h"
#include "Kitchen.h"



int main(int argc, char **argv){
    double t = 0;
    if(argc > 1){
        if(0==strcmp(argv[1],"0")){
            t = 0;
        }else if(0==strcmp(argv[1],"-5")){
            t = -5;
        }
    }

    int amountExperiments = 3;
    int timeMax = 3600 * 3;
    for(int mode = 0; mode < amountExperiments; mode++){
        if(mode == 0){
            std::cout <<"------------ Part 1 house is not isolated, ";
        }else if(mode == 1){
            std::cout << std::endl;
            std::cout <<"------------ Part 2 the house is insulated, thermally insulated with RockWool ";
        }else if(mode == 2){
            std::cout << std::endl;
            std::cout <<"------------ Part 3 the house is insulated, the facade is insulated with glass wool KNAUF the roof is insulated with RockWool ";
        }
        std::cout << "outside air temperature " << t << "C " << "experiment time " << timeMax << "s ------------" << std::endl;

        //Creating rooms
        Hall hall(mode);
        Bathroom bathroom(mode);
        Bedroom bedroom(mode);
        Kitchen kitchen(mode);

        HeatSource heatSours;
        Model model;
        House house;

        house.addRoom(&hall);
        house.addRoom(&bathroom);
        house.addRoom(&bedroom);
        house.addRoom(&kitchen);

        //start model
        model.start(timeMax, house, heatSours, t);
    }


   return 0;
}