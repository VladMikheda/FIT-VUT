/**
 * Project: Čtečka novinek ve formátu Atom a RSS s podporou TLS
 *
 * File:     UrlParser.h
 * Subject:  ISA 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 */


#ifndef ISA_URLPARSER_H
#define ISA_URLPARSER_H
#include "Error.h"
#include <regex>
#include <string>
/**
 *The class checks if the URL is correct
 * and parses the individual parts from it
 */
class UrlParser {

private:

    const u_int8_t schemeNumber = 1;
    const u_int8_t domainNameNumber = 2;
    const u_int8_t portNumber = 3;
    const u_int8_t patchNumber = 4;
    const u_int8_t parametersNumber = 5;
    const u_int8_t fragmentNumber = 6;

    const u_int16_t httpPort = 80;
    const u_int16_t  httpsPort = 443;
    const std::string HTTP = "http";
    const std::string HTTPS = "https";
    const std::string regexUrl =  "^(http|https)://([a-zA-Z\\.0-9-]+)(:[0-9]+)?(/[^:?#]*)?(\\?[^:#]+)?(#.+)?$";
//    const std::string regexUrl =  "^(http|https)://[a-zA-Z\\.0-9-]+(:[0-9]+.+|[^:]+)$";

    int port = 0;
    bool httpScheme = false;
    bool httpsScheme = false;
    std::string *stringPort = nullptr;
    std::string *domainName = nullptr;
    std::string *path = nullptr;
    std::string *parameters = nullptr;
    std::string *fragment = nullptr;

    void parseScheme(const std::string& scheme);
    bool parsePort();

public:
    bool parse(const std::string& urlArgument);
    std::string* getStringPort() const;
    bool getHttpScheme() const;
    bool getHttpsScheme() const;
    std::string* getDomainName() const;
    std::string* getPath() const;
    std::string* getParameters() const;
    std::string* getFragment() const;
    void reset();

    ~UrlParser();
};


#endif //ISA_URLPARSER_H