/**
 * Project: Čtečka novinek ve formátu Atom a RSS s podporou TLS
 *
 * File:     ParseArguments.h
 * Subject:  ISA 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 */


#ifndef ISA_PARSEARGUMENTS_H
#define ISA_PARSEARGUMENTS_H
#include "Error.h"
#include "UrlParser.h"

/**
 * The class parses the arguments and checks whether they are valid or not
 */
class ParseArguments {

private:
    //const arguments
    const std::string CERTIFICATE_FILE = "c";
    const std::string CERTIFICATE_DIRECTORY = "C";
    const std::string FEED_FILE = "f";
    const std::string TIME_CHANGE = "T";
    const std::string NAME_AUTHOR = "a";
    const std::string ASSOCIATED_URL = "u";
    const std::string HELP = "h";
    bool helpFlag = false;

    // main arguments
    std::string* url = nullptr;
    std::string* feedFilePath = nullptr;
    std::string* certificateFilePath = nullptr;
    std::string* certificateDirectoryPath = nullptr;
    bool time = false;
    bool author = false;
    bool associateUrl = false;

    std::string searchArgument(char* arg);
    bool checkArgumentValue(int argc, int number);
//    void cleanAll();


public:
    ~ParseArguments();
    bool isTime() const;
    bool isAuthor() const;
    bool isAssociateUrl() const;
    std::string* getUrl() const;
    std::string* getFeedFilePath() const;
    std::string* getCertificateFilePath() const;
    std::string* getCertificateDirectoryPath() const;
    bool checkArguments(int argc, char** argv);
    bool isHelp();
};



#endif //ISA_PARSEARGUMENTS_H
