/**
 * Project: Čtečka novinek ve formátu Atom a RSS s podporou TLS
 *
 * File:     FeedReader.cpp
 * Subject:  ISA 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 */

#include "FeedReader.h"

/**
 * The main method of the program,
 * parses the arguments, enters the loop in which it establishes connections and parses the received answers
 * @param argc Number of arguments accepted by the program
 * @param argv Accepted arguments by the program
 */
bool FeedReader::read(int argc, char **argv) {

    ParseArguments parseArguments;
    //call method to parse arguments
    if(!parseArguments.checkArguments(argc,argv)){
        return false;
    }
    if(parseArguments.isHelp()){
        return true;
    }

    //if the file is set, we read from the file and add all the URLs to the list
    // if not, add the specified url
    if(parseArguments.getFeedFilePath()){
        if(!readFile(parseArguments.getFeedFilePath())){
            Error::errorPrint(Error::ERROR_NOT_OPEN_FILE);
            return false;
        }
    }else{
        urlList.push_back(*parseArguments.getUrl());
    }

    UrlParser urlParser;
    Connect connect;
    connect.initialization();
    XMLParser xmlParser;

    //main program loop
    for(const std::string& urlString : urlList){

        //url string parse -> domain, port...
        if(!urlParser.parse(urlString)){
            Error::printMessage("URL: " + urlString);
            resetAll(connect,xmlParser,urlParser);
            continue;
        }

        //concatenate domain name and port to get connection address
        generateDomainNamePort(*urlParser.getDomainName(),*urlParser.getStringPort());
        generateRequest(urlParser);

        //connection is established depending on the scheme
        if(urlParser.getHttpsScheme()){
            //initialize structure to hold the sll information
            connect.initializationSslConnect();

            if(!getCertificate(parseArguments,connect)){
                Error::printMessage("URL: " + urlString);
                resetAll(connect,xmlParser,urlParser);
                continue;
            }

            if(!connect.settingBio()){
                Error::printMessage("URL: " + urlString);
                resetAll(connect,xmlParser,urlParser);
                continue;
            }

            if(!connect.sslConnect(domainNamePort,*urlParser.getDomainName())){
                Error::printMessage("URL: " + urlString);
                resetAll(connect,xmlParser,urlParser);
                continue;
            }

            if(!connect.checkConnect()){
                Error::printMessage("URL: " + urlString);
                resetAll(connect,xmlParser,urlParser);
                continue;
            }

            if(!connect.isCertificateValid()){
                Error::printMessage("URL: " + urlString);
                resetAll(connect,xmlParser,urlParser);
                continue;
            }

        }else if(urlParser.getHttpScheme()){
            if(!connect.insecureConnect(domainNamePort)){
                Error::printMessage("URL: " + urlString);
                resetAll(connect,xmlParser,urlParser);
                continue;
            }
            if(!connect.checkConnect()){
                Error::printMessage("URL: " + urlString);
                resetAll(connect,xmlParser,urlParser);
                continue;
            }
        }


        if(!connect.sendRequest(request)){
            Error::printMessage("URL: " + urlString);
            resetAll(connect,xmlParser,urlParser);
            continue;
        }

        std::string response = "";
        if(!connect.readResponse(response)){
            Error::printMessage("URL: " + urlString);
            resetAll(connect,xmlParser,urlParser);
            continue;
        }

//        std::cout << response << std::endl;

        std::string xmlString{0};
        if(!findXML(response,xmlString)){
            Error::printMessage("URL: " + urlString);
            resetAll(connect,xmlParser,urlParser);
            continue;
        }

        xmlParser.setArguments(parseArguments.isAssociateUrl(), parseArguments.isAuthor(), parseArguments.isTime());
        if(!xmlParser.parse(xmlString)){
            Error::printMessage("URL: " + urlString);
            resetAll(connect,xmlParser,urlParser);
            xmlParser.reset();
            continue;
        }

        resetAll(connect,xmlParser,urlParser);
        xmlParser.reset();

    }
    resetAll(connect,xmlParser,urlParser);
    xmlParser.reset();
    connect.fullExit();

    return true;
}

/**
 * parse the response and separate the headers from the body
 * @param response response from the server
 * @param xmlString string with xml response
 * @return false in case of error or true the truth if successful
 */
bool FeedReader::findXML(const std::string response, std::string& xmlString) {

    size_t endFirstLine = response.find("\r\n");
    if(endFirstLine == std::string::npos){
        Error::errorPrint(Error::ERROR_NOT_CORRECT_RESPONSE);
        return false;
    }
    std::string firstLine = response.substr(0, endFirstLine);

    if(!std::regex_match(firstLine, std::regex(regexHTTPResponse))){
        Error::errorPrint(Error::ERROR_NOT_CORRECT_RESPONSE);
        return false;
    }

    size_t endHTTPHeader = response.find(HTTPSeparator);
    if(endHTTPHeader == std::string::npos){
        Error::errorPrint(Error::ERROR_RESPONSE_HAS_NO_BODY);
        return false;
    }

    endHTTPHeader+=HTTPSeparator.length();

    xmlString = response.substr(endHTTPHeader);

    return true;
}

/**
 * connects domain name and port
 */
void FeedReader::generateDomainNamePort(const std::string& domainName, const std::string& port) {
    domainNamePort = domainName + ":" + port;
}

/**
 * Generates a request
 * @param urlParser reference to class instance urlParser
 */
void FeedReader::generateRequest(UrlParser &urlParser) {
    const std::string userAgent = "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/51.0.2704.103 Safari/537.36";
    std::string fullPath = "/";
    if(urlParser.getPath()){
        fullPath = *urlParser.getPath();
    }
    if(urlParser.getParameters()){
        fullPath += *urlParser.getParameters();
    }
    if(urlParser.getFragment()){
        fullPath += *urlParser.getFragment();
    }

    request = "GET " + fullPath + " HTTP/1.0\r\n"
              + "Host:" + *urlParser.getDomainName() + "\r\n"
              + "Connection:Close"+ "\r\n"
              + "User-Agent:" + userAgent + "\r\n\r\n";
}

/**
 * Selects which certificate to use (standard or user-defined)
 * @param parseArguments user specified arguments
 * @param connect reference to class instance Connect
 * @return
 */
bool FeedReader::getCertificate(ParseArguments &parseArguments, Connect &connect) {
    if(parseArguments.getCertificateFilePath() && parseArguments.getCertificateDirectoryPath()){

        std::string certificateFilePath = *parseArguments.getCertificateFilePath();
        std::string certificateDirPath = *parseArguments.getCertificateDirectoryPath();
        return connect.addSslCertificateAndDir(certificateFilePath,certificateDirPath);

    }else if(parseArguments.getCertificateFilePath()){

        std::string certificateFilePath = *parseArguments.getCertificateFilePath();
        return connect.addSslCertificate(certificateFilePath);

    }else if(parseArguments.getCertificateDirectoryPath()){

        std::string certificateDirPath = *parseArguments.getCertificateDirectoryPath();
        return connect.addSslCertificateDir(certificateDirPath);

    }else{
        return connect.addDefaultSslCertificate();
    }
}

/**
 *Method for reading URL addresses from a given file
 * @param filePath path to given file
 */
bool FeedReader::readFile(const std::string *filePath) {
    std::ifstream file (*filePath);
    if(!file){
        return false;
    }

    std::string fileLine{0};
    while(!file.eof()){
        getline(file,fileLine);
        if(!std::regex_match(fileLine, std::regex(regexComment))){
            urlList.push_back(fileLine);
        }
    }
    file.close();
    return true;
}
/**
 * Reset all parameters for reuse
 * @param connect reference to class instance Connect
 * @param xmlParser reference to class instance XMLParser
 * @param urlParser reference to class instance URLParser
 */
void FeedReader::resetAll(Connect& connect, XMLParser& xmlParser, UrlParser& urlParser) {
    domainNamePort = "\0";
    request = "\0";
    connect.closeConnect();
    urlParser.reset();
    xmlParser.reset();
}



