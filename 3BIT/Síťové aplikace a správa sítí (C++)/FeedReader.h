/**
 * Project: Čtečka novinek ve formátu Atom a RSS s podporou TLS
 *
 * File:     FeedReader.h
 * Subject:  ISA 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 */
#ifndef ISA_FEEDREADER_H
#define ISA_FEEDREADER_H
#include "ParseArguments.h"
#include "XMLParser.h"
#include <list>
#include <csignal>
#include "Connect.h"
#include <fstream>

/**
 * The main class is used as the main one in the program
 * and calls the methods of the others of the classes,
 * starting from parsing the arguments and ending with the output of the result.
 */
class FeedReader {

public:
    std::list<std::string> urlList;

    bool read(int argc, char** argv);
private:
    const std::string HTTPSeparator = "\r\n\r\n";
    const std::string regexComment = "(^\\s*#.*$)|(^\\s*$)";
    const std::string regexHTTPResponse = "^HTTP\\/[0-2].[0-1]\\s2[0-9][0-9].*$";

    std::string domainNamePort{0};
    std::string request{0};
    void generateDomainNamePort(const std::string& domainName, const std::string& port);
    void generateRequest(UrlParser &urlParser);
    bool getCertificate(ParseArguments &parseArguments, Connect &connect);
    bool readFile(const std::string *filePath);
    bool findXML(const std::string response, std::string& xmlString);
    void resetAll(Connect& connect, XMLParser& xmlParser, UrlParser& urlParser);

};

#endif //ISA_FEEDREADER_H
