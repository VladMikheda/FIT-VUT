/**
 * Project: Model vytapeni (Teplarenstvi)
 *
 * File:     House.h
 * Subject:  IMS 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 * @author:  Vladislav Khrisanov xkhris00
 */

#ifndef MODEL_HOUSE_H
#define MODEL_HOUSE_H
#include <list>
#include "IRoom.h"


class House {

public:
    std::list<IRoom*> rooms;
    double averageHeatInWalls = 15;
    int amountRoom = 0;
    void addRoom(IRoom* room);
};


#endif //MODEL_HOUSE_H
