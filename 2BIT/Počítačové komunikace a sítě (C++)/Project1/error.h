/**
 * Project: Vytvoření serveru komunikujícího prostřednictvím protokolu HTTP
 *
 * File:     error.h
 * Subject:  IPK 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 */

#ifndef IPK_PROJ1CPP_ERROR_H
#define IPK_PROJ1CPP_ERROR_H

#include <iostream>

enum error {
    ERROR_PORT = 5,
    ERROR_CREATE_SOCET = -1,
    ERROR_SETSOCKETOPT = -2,
    ERROR_BIND = -3,
    ERROR_LISTEN = -4,
    ERROR_ACCEPT = -5
};

#endif //IPK_PROJ1CPP_ERROR_H
