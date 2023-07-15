/**
 * Project: Čtečka novinek ve formátu Atom a RSS s podporou TLS
 *
 * File:     ParseArguments.cpp
 * Subject:  ISA 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 */

#include "ParseArguments.h"

/**
 * Class destructor
 */
ParseArguments::~ParseArguments(){
    delete url;
    delete feedFilePath;
    delete certificateFilePath;
    delete certificateDirectoryPath;
}

/**
 * The method of deallocation the memory of variables
 * Called on errors
 */
//void ParseArguments::cleanAll() {
//    delete url;
//    delete feedFilePath;
//    delete certificateFilePath;
//    delete certificateDirectoryPath;
//    url = nullptr;
//    feedFilePath = nullptr;
//    certificateFilePath= nullptr;
//    certificateDirectoryPath= nullptr;
//}

/**
 * The main method in the class runs the argument check
 * @param argc Number of arguments accepted by the program
 * @param argv Accepted arguments by the program
 */
bool ParseArguments::checkArguments(int argc, char** argv){

    for (int i = 1; i < argc; i++){
        std::string argument = searchArgument(argv[i]);
        if(argument == HELP){
            Error::helpOut();
            helpFlag = true;
            return true;
        }
    }

    for (int i = 1; i < argc; i++){

        //parse argument to string
        std::string argument = searchArgument(argv[i]);

        //checking parsed arguments for correctness
        if(argument == CERTIFICATE_FILE){

            if(certificateFilePath){
                Error::errorPrint(Error::ERROR_ARGUMENT_REPEAT);
                return false;
            }

            if(!checkArgumentValue(argc, i)){
                return false;
            }
            certificateFilePath = new std::string(argv[++i]); // path entry for the certificate

        }else if(argument == CERTIFICATE_DIRECTORY){

            if(certificateDirectoryPath){
                Error::errorPrint(Error::ERROR_ARGUMENT_REPEAT);
                return false;
            }

            if(!checkArgumentValue(argc, i)){
                return false;
            }
            certificateDirectoryPath = new std::string(argv[++i]);

        }else if(argument == FEED_FILE){

            if(feedFilePath){
                Error::errorPrint(Error::ERROR_ARGUMENT_REPEAT);
                return false;
            }

            if(!checkArgumentValue(argc,i)){
                return false;
            }
            feedFilePath = new std::string(argv[++i]);

        }else if(argument == TIME_CHANGE){

            if(time) {
                Error::errorPrint(Error::ERROR_ARGUMENT_REPEAT);
                return false;
            }
            time = true;

        }else if(argument == NAME_AUTHOR){

            if(author) {
                Error::errorPrint(Error::ERROR_ARGUMENT_REPEAT);
                return false;
            }
            author = true;

        }else if(argument == ASSOCIATED_URL){

            if(associateUrl) {
                Error::errorPrint(Error::ERROR_ARGUMENT_REPEAT);
                return false;
            }
            associateUrl = true;

        }else{
            if(url) {
                Error::errorPrint(Error::ERROR_ARGUMENT_REPEAT);
                return false;
            }
            url = new std::string(argv[i]);
        }

    }

    if((!url && !feedFilePath) || (url && feedFilePath)){
        Error::errorPrint(Error::ERROR_URL_OR_FEED_FILE);
        return false;
    }

    return true;
}

/**
 * Preparation of arguments for verification
 * Separation of the sign '-'
 * @param arg argument
 * @return processed argument
 */
std::string ParseArguments::searchArgument(char *arg) {
    return (arg[0] == '-') ? std::string {&arg[1]} : std::string(arg);
}

/**
 * checking if a value follows an argument
 * @param argc Number of arguments accepted by the program
 * @param number Argument serial number
 */
bool ParseArguments::checkArgumentValue(int argc, int number) {
    if(number + 1 >=  argc){
        Error::errorPrint(Error::ERROR_ARGUMENT_NOT_VALUE);
        return false;
    }
    return true;
}


bool ParseArguments::isTime() const {
    return time;
}

bool ParseArguments::isAuthor() const {
    return author;
}

bool ParseArguments::isAssociateUrl() const {
    return associateUrl;
}

std::string* ParseArguments::getUrl() const {
    return url;
}

std::string* ParseArguments::getFeedFilePath() const {
    return feedFilePath;
}

std::string* ParseArguments::getCertificateFilePath() const {
    return certificateFilePath;
}

std::string* ParseArguments::getCertificateDirectoryPath() const {
    return certificateDirectoryPath;
}

bool ParseArguments::isHelp() {
    return helpFlag;
}

