/**
 * Project: Model vytapeni (Teplarenstvi)
 *
 * File:     House.cpp
 * Subject:  IMS 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 * @author:  Vladislav Khrisanov xkhris00
 */
#include "House.h"

void House::addRoom(IRoom *room) {
    this->amountRoom++;
    this->rooms.push_back(room);
}
