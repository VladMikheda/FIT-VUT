/**
 * Project: Model vytapeni (Teplarenstvi)
 *
 * File:     Bedroom.h
 * Subject:  IMS 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 * @author:  Vladislav Khrisanov xkhris00
 */
#ifndef MODEL_BEDROOM_H
#define MODEL_BEDROOM_H


#include "IRoom.h"

class Bedroom : public IRoom{

public:

    Bedroom(int mode);

    double wallInS() const;
    double wallOutS() const;
    double roofOutS() const;

    double allRoofOutR() const;
    double allInR() const;
    double allOutR() const;


};


#endif //MODEL_BEDROOM_H
