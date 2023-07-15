/**
 * Project: Čtečka novinek ve formátu Atom a RSS s podporou TLS (Tests)
 *
 * File:     test.cpp
 * Subject:  ISA 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 */

#include "UnitTests.h"

/**
 * Main file for running unit tests
 * @return
 */
int main(int argc, char** argv ){
    UnitTests unitTests;
    unitTests.testArgumentParser();
    unitTests.testURLParser();
    if(argc > 1){
        if(strcmp(argv[1],"nocert") == 0)
            unitTests.testConnect(false);
        else{
            unitTests.testConnect(true);
        }
    }else{
        unitTests.testConnect(true);
    };
    return 0;
}