/**
 * Project: Čtečka novinek ve formátu Atom a RSS s podporou TLS
 *
 * File:     main.cpp
 * Subject:  ISA 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 */


#include "FeedReader.h"

/**
 * The main function of the program,
 * entrance to the program
 * creates an instance of the FeedReader class and launches their main functions
 */
int main(int argc, char** argv) {

    FeedReader feedReader;
    int exit = Error::SUCCESS;
    if(!feedReader.read(argc,argv)){
        exit = Error::EXIT_FAIL;
    }
    return exit;
}