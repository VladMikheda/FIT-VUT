/**
 * Project: Model vytapeni (Teplarenstvi)
 *
 * File:     Kitchen.h
 * Subject:  IMS 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 * @author:  Vladislav Khrisanov xkhris00
 */

#ifndef MODEL_KITCHEN_H
#define MODEL_KITCHEN_H


#include "IRoom.h"

class Kitchen : public IRoom {
public:
    Kitchen(int mode);
    double wallInS() const;
    double wallOutS() const;
    double roofOutS() const;

    double allRoofOutR() const;
    double allInR() const;
    double allOutR() const;

};


#endif //MODEL_KITCHEN_H
