/**
 * Project: Čtečka novinek ve formátu Atom a RSS s podporou TLS (Tests)
 *
 * File:     UnitTests.h
 * Subject:  ISA 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 */


#ifndef ISA_UNITTESTS_H
#define ISA_UNITTESTS_H

#include "../../ParseArguments.h"
#include "../../XMLParser.h"
#include "../../Connect.h"

#include "TestArgumentParser.h"
#include "TestUrlParser.h"
#include "TestConnect.h"


#include <iostream>
/**
 * Main class to run all unit tests
 */
class UnitTests {

public:
    void testArgumentParser();
    void testURLParser();
    void testConnect(bool testsCertificate);
};


#endif //ISA_UNITTESTS_H
