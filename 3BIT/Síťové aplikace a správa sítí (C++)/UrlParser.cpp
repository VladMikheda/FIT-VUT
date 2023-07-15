/**
 * Project: Čtečka novinek ve formátu Atom a RSS s podporou TLS
 *
 * File:     UrlParser.cpp
 * Subject:  ISA 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 */

#include "UrlParser.h"

/**
 * Class destructor
 */
UrlParser::~UrlParser(){
    delete stringPort;
    delete domainName;
    delete path;
    delete parameters;
    delete fragment;
}

/**
 * The main method, parsing and checks the URL address into separate parts
 *
 * @param urlArgument URL-address that the user specified or the address read from the file that the user specified
 * @return true or false depending on whether the URL-address is correct
 */
bool UrlParser::parse(const std::string& urlArgument) {

    //validating the URL with a regular expression
    //if the address is correct, then it is split into parts
    std::smatch allParts;
    if(!std::regex_match(urlArgument, allParts, std::regex(regexUrl))){
        Error::errorPrint(Error::ERROR_URL_INVALID);
        return false;
    }


    //checking and writing parts of a URL


    parseScheme(allParts[schemeNumber].str());

    domainName = new std::string(allParts[domainNameNumber].str());

    if(!allParts[portNumber].str().empty()){
        const u_int8_t colonPosition = 1;
        stringPort = new std::string (allParts[portNumber].str().substr(colonPosition));
    }

    if(!parsePort()){
        return false;
    }

    if(!allParts[patchNumber].str().empty()){
        path = new std::string (allParts[patchNumber].str());
    }

    if(!allParts[parametersNumber].str().empty()){
        parameters = new std::string (allParts[parametersNumber].str());
    }

    if(!allParts[fragmentNumber].str().empty()){
        fragment = new std::string (allParts[fragmentNumber].str());
    }

    return true;
}

/**
 * Schema definition
 * @param scheme parsed scheme parameter
 */
void UrlParser::parseScheme(const std::string& scheme) {
    if(scheme == HTTP){
        httpScheme = true;
    }else if(scheme == HTTPS){
        httpsScheme = true;
    }
}

/**
 *Verifying that the port is set correctly
 *If the port is not set, it is assigned depending on the scheme
 */
bool UrlParser::parsePort() {

    if(stringPort){
        try{
            port = stoi(*stringPort, nullptr,10);
        }catch(std::exception const& e){
            Error::errorPrint(Error::ERROR_PORT_INVALID);
            return false;
        }

        if(port > 65535 || port < 1){
            Error::errorPrint(Error::ERROR_PORT_INVALID);
            return false;
        }
    }else{
        if(httpScheme){
            port = httpPort;
        }else if(httpsScheme){
            port = httpsPort;
        }
        stringPort = new std::string(std::to_string(port));
    }

    return true;

}

/**
 * The method resets the values of all parameters
 */
void UrlParser::reset(){
    delete stringPort;
    delete domainName;
    delete path;
    delete parameters;
    delete fragment;

    stringPort = nullptr;
    domainName = nullptr;
    path = nullptr;
    parameters = nullptr;
    fragment = nullptr;

    httpScheme = false;
    httpsScheme = false;
    port = 0;
}

std::string* UrlParser::getStringPort() const {
    return stringPort;
}

std::string* UrlParser::getDomainName() const{
    return domainName;
}

std::string* UrlParser::getPath() const{
    return path;
}

std::string* UrlParser::getParameters() const {
    return parameters;
}

bool UrlParser::getHttpScheme() const {
    return httpScheme;
}

bool UrlParser::getHttpsScheme() const{
    return httpsScheme;
}

std::string *UrlParser::getFragment() const {
    return fragment;
}


