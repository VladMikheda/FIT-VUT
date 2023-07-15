/**
 * Project: Čtečka novinek ve formátu Atom a RSS s podporou TLS
 *
 * File:     XMLParser.cpp
 * Subject:  ISA 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 */
#include "XMLParser.h"


/**
 * The main function checks the format of the XML file and sends parsing it
 * @param xmlString input xml file
 * @return true on success and false on failure
 */
bool XMLParser::parse(const std::string& xmlString) {

    //check and create xml doc
    try{
        xmlSetGenericErrorFunc(nullptr, reinterpret_cast<xmlGenericErrorFunc>(XMLParser::nullXmlGeneralErrorFunction));
        xmlThrDefSetGenericErrorFunc(nullptr, reinterpret_cast<xmlGenericErrorFunc>(XMLParser::nullXmlGeneralErrorFunction));
        doc = xmlParseDoc((xmlChar*)xmlString.c_str());
    }catch(int e){
        return false;
    }
    if(!doc){
        Error::errorPrint(Error::ERROR_NOT_OPEN_XML_DOC);
        return false;
    }

    //get the main node of the xml
    rootElement = xmlDocGetRootElement(doc);
    if(!rootElement){
        Error::errorPrint(Error::ERROR_NOT_EXIST_ROOT_ELEMENT);
        return false;
    }

    if(!checkFormat()){
        return false;
    }

    //parsing
    if(rss){
        parseInformationRSS();
    }else if(atom){
        parseFeedAtom();
    }

    return true;
}

/**
 * Сhecking if the xml format matches atom or rss
 * @return true on format is correct and false on format incorrect
 */
bool XMLParser::checkFormat() {

    if(!xmlStrcmp(rootElement->name, (const xmlChar*)"rss")){
        if(!xmlStrcmp(rootElement->properties->children->content, (const xmlChar*)"2.0")){
            rss = true;
        }else{
            Error::errorPrint(Error::ERROR_NOT_SUPPORTED_RSS_VERSION);
            return false;
        }
    }else if(!xmlStrcmp(rootElement->name, (const xmlChar*)"feed")){
        atom = true;
    }else{
        Error::errorPrint(Error::ERROR_NOT_SUPPORTED_FORMAT);
        return false;
    }

    return true;
}

/**
 * Parsing the start node
 */
void XMLParser::parseFeedAtom() {
    xmlChar* mainTitle = nullptr;
    for( xmlNode *mainNode = rootElement->children; mainNode; mainNode = mainNode->next){

        if(!xmlStrcmp(mainNode->name, (const xmlChar*)"title")) {
            mainTitle = xmlNodeGetContent(mainNode);
        }
    }
    printMainTitle(mainTitle);
    xmlFree(mainTitle);
    mainTitle = nullptr;

    for( xmlNode *mainNode = rootElement->children; mainNode; mainNode = mainNode->next){

        if(!xmlStrcmp(mainNode->name, (const xmlChar*)"entry")) {
            parseRecordsAtom(mainNode);
        }
    }

}

/**
 * Parsing sub-nodes and collecting information about individual articles
 * @param entryNode pointer to a list with sub-nodes
 */
void XMLParser::parseRecordsAtom(xmlNode* entryNode) {
    xmlChar *elements[ALL_ITEM_ELEMENT]{nullptr,nullptr,nullptr,nullptr};

    for(xmlNode *itemNode = entryNode->children; itemNode; itemNode = itemNode->next) {
        if (!xmlStrcmp(itemNode->name, (const xmlChar *) "title")) {
            elements[TITLE] = xmlNodeGetContent(itemNode);
        }
        else if (url && (!xmlStrcmp(itemNode->name, (const xmlChar *) "link"))) {
            parseLinkAtom(itemNode, elements);
        }
        else if (author && (!xmlStrcmp(itemNode->name, (const xmlChar *) "author"))) {
            parseAuthorAtom(itemNode,elements);
        }
        else if (time && (!xmlStrcmp(itemNode->name, (const xmlChar *) "updated"))) {
            elements[TIME] = xmlNodeGetContent(itemNode);
        }
    }

    printRecordInformation(elements);
    for(int i = 0; i < ALL_ITEM_ELEMENT; i++){
        if(elements[i]){
            xmlFree(elements[i]);
        }
    }
}

/**
 * Parsing link information
 * @param itemNode pointer to node with link information
 * @param elements array for writing information
 */
void XMLParser::parseLinkAtom(xmlNode *itemNode, xmlChar **elements) {
    for(_xmlAttr *linkProperties = itemNode->properties; linkProperties; linkProperties = linkProperties->next) {
        if (!xmlStrcmp(linkProperties->name, (const xmlChar *) "href")){
            elements[LINK] = xmlNodeGetContent(linkProperties->children);
        }
    }
}

/**
 * Parsing author information
 * @param itemNode pointer to a list of sub-nodes with information about the author
 * @param elements array for writing information
 */
void XMLParser::parseAuthorAtom(xmlNode *itemNode, xmlChar **elements) {
    for(xmlNode *nameNode = itemNode->children; nameNode; nameNode = nameNode->next){
        if (!xmlStrcmp(nameNode->name, (const xmlChar *) "name")){
            elements[AUTHOR_NAME] = xmlNodeGetContent(nameNode);
        }
        else if (!xmlStrcmp(nameNode->name, (const xmlChar *) "email")){
            elements[AUTHOR] = xmlNodeGetContent(nameNode);
        }
    }
}


/**
 * Parsing the start node
 */
void XMLParser::parseInformationRSS() {

    for( xmlNode *mainNode = rootElement->children; mainNode; mainNode = mainNode->next){

        if(!xmlStrcmp(mainNode->name, (const xmlChar*)"channel")) {
            parseChannelRSS(mainNode);
        }
    }
}

/**
 * Parsing the node containing the main title and sub-nodes
 * @param mainNode pointer to a list with sub-nodes
 */
void XMLParser::parseChannelRSS(xmlNode* mainNode ) {
    xmlChar* mainTitle = nullptr;

    for(xmlNode *channelNode = mainNode->children; channelNode; channelNode = channelNode->next){

        if(!xmlStrcmp(channelNode->name, (const xmlChar*)"title")){
            mainTitle = xmlNodeGetContent(channelNode);
        }

    }

    printMainTitle(mainTitle);
    xmlFree(mainTitle);
    mainTitle = nullptr;

    for(xmlNode *channelNode = mainNode->children; channelNode; channelNode = channelNode->next){

        if(!xmlStrcmp(channelNode->name, (const xmlChar*)"item")){
            parseRecordRSS(channelNode);
        }

    }

}


/**
 * Parsing sub-nodes and collecting information about individual articles
 * @param channelNode pointer to a list with sub-nodes
 */
void XMLParser::parseRecordRSS(xmlNode* channelNode) {
    xmlChar *elements[ALL_ITEM_ELEMENT]{nullptr,nullptr,nullptr,nullptr};

    for(xmlNode *itemNode = channelNode->children; itemNode; itemNode = itemNode->next) {
        if (!xmlStrcmp(itemNode->name, (const xmlChar *) "title")) {
            elements[TITLE] = xmlNodeGetContent(itemNode);
        }
        else if (url && (!xmlStrcmp(itemNode->name, (const xmlChar *) "link"))) {
            elements[LINK] = xmlNodeGetContent(itemNode);
        }
        else if (author && (!xmlStrcmp(itemNode->name, (const xmlChar *) "author"))) {
            elements[AUTHOR] = xmlNodeGetContent(itemNode);
        }
        else if (time && (!xmlStrcmp(itemNode->name, (const xmlChar *) "pubDate"))) {
            elements[TIME] = xmlNodeGetContent(itemNode);
        }
    }

    printRecordInformation(elements);
    for(int i = 0; i < ALL_ITEM_ELEMENT; i++){
        if(elements[i]){
            xmlFree(elements[i]);
        }
    }

}

/**
 * Writes information about single elements to std out
 * @param elements array with information
 */
void XMLParser::printRecordInformation(xmlChar **elements) {

    if(elements[TITLE]){
        if(!firstItem && (url || author || time)){
            std::cout << "\n";
        }
        std::cout << elements[TITLE] << std::endl;
    }else{
        if(elements[LINK] || (elements[AUTHOR] || elements[AUTHOR_NAME]) || elements[TIME]){
            if(!firstItem){
                std::cout << "\n";
            }
            std::cout << "----" << std::endl;
        }
    }

    if(elements[LINK]){
        std::cout << "URL: " << elements[LINK] << std::endl;
    }

    if(elements[TIME]){
        if(atom){
            std::cout << "Aktualizace: " << elements[TIME] << std::endl;
        }else{
            std::cout << "Zverejneno: " << elements[TIME] << std::endl;
        }
    }

    if(elements[AUTHOR] || elements[AUTHOR_NAME]){

        std::cout << "Autor: ";
        if(elements[AUTHOR_NAME]){
            std::cout << elements[AUTHOR_NAME];
            if(elements[AUTHOR]){
                std::cout << " (" << elements[AUTHOR] << ")" << std::endl;
            }else{
                std::cout << "\n";
            }
        }else if(elements[AUTHOR]){
            std::cout << elements[AUTHOR] << std::endl;
        }

    }

    firstItem = false;

}

/**
 * Writes main title to std out
 * @param mainTitle pointer to main title
 */
void XMLParser::printMainTitle(xmlChar* mainTitle) {
    if(!firstMainTitle){
        std::cout << "\n";
    }
    if(mainTitle){
        std::cout << "*** " << mainTitle << " ***" << std::endl;
    }else{
        std::cout << "*** " << "-----" << " ***" << std::endl;
    }
    firstItem = true;
    firstMainTitle = false;

}

/**
 * Set arguments for read xml
 * @param urlArg will be read and written out URL
 * @param authorArg will be read and written out author
 * @param timeArg will be read and written out time update or time publication
 */
void XMLParser::setArguments(bool urlArg, bool authorArg, bool timeArg) {
    this->url = urlArg;
    this->author = authorArg;
    this->time = timeArg;
}

/**
 * reset method
 */
void XMLParser::reset() {
    this->url = false;
    this->author = false;
    this->time = false;

    atom = false;
    rss  = false;
    firstItem = false;
    if(doc){
        xmlFreeDoc(doc);
        xmlCleanupParser();
    }


    rootElement = nullptr;
    doc = nullptr;
}

void XMLParser::nullXmlGeneralErrorFunction(void *ctx, char *msg, ...) {
    bool log = false;
    if(log){
        if(ctx){
            std::cerr << msg << std::endl;
        }
    }
}