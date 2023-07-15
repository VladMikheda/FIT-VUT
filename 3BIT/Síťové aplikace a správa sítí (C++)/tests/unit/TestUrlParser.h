/**
 * Project: Čtečka novinek ve formátu Atom a RSS s podporou TLS (Tests)
 *
 * File:     TestUrlParser.h
 * Subject:  ISA 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 */


#ifndef ISA_TESTURLPARSER_H
#define ISA_TESTURLPARSER_H


#include <string>
#include "../../UrlParser.h"


/**
 * Unit test suite class for testing the URL parser
 */
class TestUrlParser {
private:
    const std::string urlEmpty = "";
    const std::string urlNormalHTTP = "http://en.wikipedia.org";
    const std::string urlNormalHTTPS = "https://en.wikipedia.org/";
    const std::string urlPort = "https://en.wikipedia.org:1212";
    const std::string urlRave = "qwerty";
    const std::string urlWrongScheme = "htstp://en.wikipedia.org/";
    const std::string urlWrongSlash = "http:/en.wikipedia.org/";
    const std::string urlEmptyPort = "https://en.wikipedia.org:/";
    const std::string urlWrongPortNumber = "https://en.wikipedia.org:234124/";
    const std::string urlWrongPortLetter = "https://en.wikipedia.org:dddd/";
    const std::string urlAll ="https://en.wikipedia.org/w/api.php?hidebots=1&days=7&limit=50&hidewikidata=1&action=feedrecentchanges&feedformat=atom#aaa";
    const std::string expectedDomain = "en.wikipedia.org";
public:
    void emptyUrl();
    void httpUrl();
    void httpsUrl();
    void portUrl();
    void raveUrl();
    void wrongSchemeUrl();
    void wrongSlashUrl();
    void emptyPortUrl();
    void wrongPortNumberUrl();
    void wrongPortLetterUrl();
    void allUrl();
};


#endif //ISA_TESTURLPARSER_H
