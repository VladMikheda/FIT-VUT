/**
 * Project: Čtečka novinek ve formátu Atom a RSS s podporou TLS (Tests)
 *
 * File:     UnitTests.cpp
 * Subject:  ISA 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 */


#include "UnitTests.h"

void UnitTests::testArgumentParser() {
    TestArgumentParser testArgumentsParser;

    testArgumentsParser.emptyArguments();
    testArgumentsParser.URLArgument();
    testArgumentsParser.feedFileNoPathArgument();
    testArgumentsParser.feedFileArgument();
    testArgumentsParser.urlAndFeedFileArgument();
    testArgumentsParser.certificateDirNoPathArgument();
    testArgumentsParser.certificateDirArgument();
    testArgumentsParser.certificateFileNoPathArgument();
    testArgumentsParser.certificateFileArgument();
    testArgumentsParser.certificateDirAndFileArgument();
    testArgumentsParser.printTimeArgument();
    testArgumentsParser.printAuthorArgument();
    testArgumentsParser.printUrlArgument();
    testArgumentsParser.allNormalArguments();

    std::cout << "TEST:Tests ArgumentParser are SUCCESS" << std::endl;
}

void UnitTests::testURLParser() {
    TestUrlParser testUrlParser;

    testUrlParser.emptyUrl();
    testUrlParser.emptyPortUrl();
    testUrlParser.httpUrl();
    testUrlParser.httpsUrl();
    testUrlParser.portUrl();
    testUrlParser.raveUrl();
    testUrlParser.wrongSchemeUrl();
    testUrlParser.wrongSlashUrl();
    testUrlParser.emptyPortUrl();
    testUrlParser.wrongPortNumberUrl();
    testUrlParser.wrongPortLetterUrl();
    testUrlParser.allUrl();

    std::cout << "TEST:Tests URLParser are SUCCESS" << std::endl;
}

void UnitTests::testConnect(bool testsCertificate) {
    TestConnect testConnects;

    testConnects.connectHTTP();
    testConnects.connectDefaultHTTPS();
    if(testsCertificate){
        testConnects.connectCertDirHTTPS();
        testConnects.connectCertFileHTTPS();
        testConnects.connectCertFileAndDirHTTPS();
    }
    testConnects.twoConnect();

    std::cout << "TEST:Tests Connect are SUCCESS" << std::endl;
}

