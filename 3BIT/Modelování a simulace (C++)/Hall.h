/**
 * Project: Model vytapeni (Teplarenstvi)
 *
 * File:     Hall.h
 * Subject:  IMS 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 * @author:  Vladislav Khrisanov xkhris00
 */

#ifndef MODEL_HALL_H
#define MODEL_HALL_H


#include "IRoom.h"

class Hall : public IRoom{


public:
    Hall(int mode);

    double wallInS() const;
    double wallOutS() const;
    double roofOutS() const;

    double allRoofOutR() const;
    double allInR() const;
    double allOutR() const;

};


#endif //MODEL_HALL_H
