/**
 * Project: Čtečka novinek ve formátu Atom a RSS s podporou TLS
 *
 * File:     XMLParser.h
 * Subject:  ISA 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 */

#ifndef ISA_XMLPARSER_H
#define ISA_XMLPARSER_H

#include "Error.h"
#include <libxml/parser.h>
#include <string>

#define ALL_ITEM_ELEMENT 5
/**
 * The class parses the received XML file as a string,
 * displays the elements requested
 * by the user: title, date of modification, author, link
 */
class XMLParser {

private:

    const u_int8_t TITLE = 0;
    const u_int8_t LINK = 1;
    const u_int8_t AUTHOR = 2;
    const u_int8_t TIME = 3;
    const u_int8_t AUTHOR_NAME = 4;


    bool atom = false;
    bool rss  = false;
    bool time = false;
    bool url = false;
    bool author = false;

    bool firstItem = false;
    bool firstMainTitle = true;

    xmlNode *rootElement = nullptr;
    xmlDoc *doc = nullptr;

    bool checkFormat();
    void parseFeedAtom();
    void parseRecordsAtom(xmlNode* entryNode );
    void parseLinkAtom(xmlNode *itemNode, xmlChar **elements);
    void parseAuthorAtom(xmlNode *itemNode, xmlChar **elements);
    void parseInformationRSS();
    void parseChannelRSS(xmlNode* mainNode);
    void parseRecordRSS(xmlNode* channelNode);
    void printMainTitle(xmlChar* mainTitle);
    void printRecordInformation(xmlChar **elements);

public:
    void setArguments(bool urlArg, bool authorArg, bool timeArg);
    void reset();
    bool parse(const std::string& xmlString);

    static void nullXmlGeneralErrorFunction(void* ctx, char* msg, ...);
};


#endif //ISA_XMLPARSER_H