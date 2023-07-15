/**
 * Project: Čtečka novinek ve formátu Atom a RSS s podporou TLS (Tests)
 *
 * File:     TestUrlParser.cpp
 * Subject:  ISA 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 */



#include <cassert>
#include "TestUrlParser.h"

void TestUrlParser::emptyUrl() {
    UrlParser urlParser;

    bool expectedCode = false;

    bool returnCode = urlParser.parse(urlEmpty);

    assert(expectedCode == returnCode);

}

void TestUrlParser::httpUrl() {
    UrlParser urlParser;

    bool expectedCode = true;
    std::string expectedPort = "80";

    bool returnCode = urlParser.parse(urlNormalHTTP);

    assert(expectedCode == returnCode);

    assert(urlParser.getStringPort() != nullptr);
    assert(expectedPort.compare(*urlParser.getStringPort()) == 0);

    assert(urlParser.getHttpScheme() == true);
    assert(urlParser.getHttpsScheme() == false);

    assert(urlParser.getDomainName() != nullptr);
    assert(expectedDomain.compare(*urlParser.getDomainName()) == 0);

}

void TestUrlParser::httpsUrl() {
    UrlParser urlParser;

    bool expectedCode = true;
    std::string expectedPort = "443";

    bool returnCode = urlParser.parse(urlNormalHTTPS);

    assert(expectedCode == returnCode);

    assert(urlParser.getStringPort() != nullptr);
    assert(expectedPort.compare(*urlParser.getStringPort()) == 0);

    assert(urlParser.getHttpsScheme() == true);
    assert(urlParser.getHttpScheme() == false);

    assert(urlParser.getDomainName() != nullptr);
    assert(expectedDomain.compare(*urlParser.getDomainName()) == 0);
}

void TestUrlParser::portUrl() {
    UrlParser urlParser;

    bool expectedCode = true;
    std::string expectedPort = "1212";

    bool returnCode = urlParser.parse(urlPort);

    assert(expectedCode == returnCode);

    assert(urlParser.getStringPort() != nullptr);
    assert(expectedPort.compare(*urlParser.getStringPort()) == 0);

    assert(urlParser.getHttpsScheme() == true);
    assert(urlParser.getHttpScheme() == false);

    assert(urlParser.getDomainName() != nullptr);
    assert(expectedDomain.compare(*urlParser.getDomainName()) == 0);
}

void TestUrlParser::raveUrl() {
    UrlParser urlParser;

    bool expectedCode = false;

    bool returnCode = urlParser.parse(urlRave);

    assert(expectedCode == returnCode);
}

void TestUrlParser::wrongSchemeUrl() {
    UrlParser urlParser;

    bool expectedCode = false;

    bool returnCode = urlParser.parse(urlWrongScheme);

    assert(expectedCode == returnCode);
}

void TestUrlParser::wrongSlashUrl() {
    UrlParser urlParser;

    bool expectedCode = false;

    bool returnCode = urlParser.parse(urlWrongSlash);

    assert(expectedCode == returnCode);
}

void TestUrlParser::emptyPortUrl() {
    UrlParser urlParser;

    bool expectedCode = false;

    bool returnCode = urlParser.parse(urlEmptyPort);

    assert(expectedCode == returnCode);
}

void TestUrlParser::wrongPortNumberUrl() {
    UrlParser urlParser;

    bool expectedCode = false;

    bool returnCode = urlParser.parse(urlWrongPortNumber);

    assert(expectedCode == returnCode);
}

void TestUrlParser::wrongPortLetterUrl() {
    UrlParser urlParser;

    bool expectedCode = false;

    bool returnCode = urlParser.parse(urlWrongPortLetter);

    assert(expectedCode == returnCode);
}

void TestUrlParser::allUrl() {
    UrlParser urlParser;

    bool expectedCode = true;
    std::string expectedPort = "443";
    std::string expectedPatch = "/w/api.php";
    std::string expectedParameters = "?hidebots=1&days=7&limit=50&hidewikidata=1&action=feedrecentchanges&feedformat=atom";
    std::string expectedFragment = "#aaa";

    bool returnCode = urlParser.parse(urlAll);

    assert(expectedCode == returnCode);

    assert(urlParser.getStringPort() != nullptr);
    assert(expectedPort.compare(*urlParser.getStringPort()) == 0);

    assert(urlParser.getHttpsScheme() == true);
    assert(urlParser.getHttpScheme() == false);

    assert(urlParser.getDomainName() != nullptr);
    assert(expectedDomain.compare(*urlParser.getDomainName()) == 0);

    assert(urlParser.getPath() != nullptr);
    assert(expectedPatch.compare(*urlParser.getPath()) == 0);

    assert(urlParser.getParameters() != nullptr);
    assert(expectedParameters.compare(*urlParser.getParameters()) == 0);

    assert(urlParser.getFragment() != nullptr);
    assert(expectedFragment.compare(*urlParser.getFragment()) == 0);

}
