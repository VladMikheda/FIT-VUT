/**
 * Project: Model vytapeni (Teplarenstvi)
 *
 * File:     Weather.h
 * Subject:  IMS 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 * @author:  Vladislav Khrisanov xkhris00
 */

#ifndef MODEL_WEATHER_H
#define MODEL_WEATHER_H


class Weather {
public:
    double getWeather();
    Weather(double t);
private:
    double t;
};


#endif //MODEL_WEATHER_H
