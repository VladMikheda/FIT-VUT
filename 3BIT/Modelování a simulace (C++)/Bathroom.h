/**
 * Project: Model vytapeni (Teplarenstvi)
 *
 * File:     Bathroom.h
 * Subject:  IMS 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 * @author:  Vladislav Khrisanov xkhris00
 */
#ifndef MODEL_BATHROOM_H
#define MODEL_BATHROOM_H

#include "IRoom.h"

class Bathroom : public IRoom{

public:
    Bathroom(int mode);
    double wallInS() const ;
    double wallOutS() const;
    double roofOutS() const;

    double allRoofOutR() const;
    double allInR() const;
    double allOutR() const;

};



#endif //MODEL_BATHROOM_H
