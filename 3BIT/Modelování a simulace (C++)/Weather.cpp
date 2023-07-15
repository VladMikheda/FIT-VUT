/**
 * Project: Model vytapeni (Teplarenstvi)
 *
 * File:     Weather.cpp
 * Subject:  IMS 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 * @author:  Vladislav Khrisanov xkhris00
 */
#include "Weather.h"

double Weather::getWeather() {
    return this->t;
}

Weather::Weather(double t) {
    this->t = t;
}
