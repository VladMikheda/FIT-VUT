/**
 * Project: Čtečka novinek ve formátu Atom a RSS s podporou TLS (Tests)
 *
 * File:     TestArgumentParser.cpp
 * Subject:  ISA 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 */

#include "TestArgumentParser.h"

void TestArgumentParser::emptyArguments() {

    ParseArguments parseArguments;

    int argumentsCount = 1;
    char *arguments[] = {&programName[0]};

    bool expectedCode = 0;
    bool returnCode = parseArguments.checkArguments(argumentsCount,arguments);

    assert(expectedCode==returnCode);

}

void TestArgumentParser::URLArgument() {

    ParseArguments parseArguments;

    int argumentsCount = 2;
    char *arguments[] = {&programName[0], &urlSting[0]};

    bool expectedCode = true;
    std::string expectUrl = urlSting;


    bool returnCode = parseArguments.checkArguments(argumentsCount,arguments);
    std::string *urlReturn = parseArguments.getUrl();
    std::string *feedFilePathReturn = parseArguments.getFeedFilePath();


    assert(expectedCode == returnCode);
    assert(urlReturn != nullptr);
    assert(((*urlReturn).compare(expectUrl)) == 0);
    assert(feedFilePathReturn == nullptr);

}

void TestArgumentParser::feedFileNoPathArgument() {
    ParseArguments parseArguments;

    int argumentsCount = 2;
    char *arguments[] = {&programName[0],&argumentFeedList[0]};

    bool expectedCode = false;


    bool returnCode = parseArguments.checkArguments(argumentsCount,arguments);

    assert(expectedCode == returnCode);


}

void TestArgumentParser::feedFileArgument() {
    ParseArguments parseArguments;

    int argumentsCount = 3;
    char *arguments[] = {&programName[0], &argumentFeedList[0], &feedFilePath[0]};

    bool expectedCode = true;
    std::string expectFeedFilePath = feedFilePath;

    bool returnCode = parseArguments.checkArguments(argumentsCount,arguments);
    std::string *urlReturn = parseArguments.getUrl();
    std::string *feedFilePathReturn = parseArguments.getFeedFilePath();

    assert(expectedCode == returnCode);

    assert(urlReturn == nullptr);

    assert(feedFilePathReturn != nullptr);
    assert(((*feedFilePathReturn).compare(expectFeedFilePath)) == 0);
}

void TestArgumentParser::urlAndFeedFileArgument() {
    ParseArguments parseArguments;

    int argumentsCount = 4;
    char *arguments[] = {&programName[0], &urlSting[0], &argumentFeedList[0], &feedFilePath[0]};

    bool expectedCode = false;

    bool returnCode = parseArguments.checkArguments(argumentsCount,arguments);

    assert(expectedCode == returnCode);

}

void TestArgumentParser::certificateDirNoPathArgument() {
    ParseArguments parseArguments;

    int argumentsCount = 3;
    char *arguments[] = {&programName[0],&urlSting[0],&argumentCertificateDir[0]};

    bool expectedCode = false;


    bool returnCode = parseArguments.checkArguments(argumentsCount,arguments);

    assert(expectedCode == returnCode);

}

void TestArgumentParser::certificateDirArgument() {
    ParseArguments parseArguments;

    int argumentsCount = 4;
    char *arguments[] = {&programName[0],&urlSting[0],
                         &argumentCertificateDir[0], &certificateDirPath[0]};

    bool expectedCode = true;
    std::string certPathReturn = certificateDirPath;


    bool returnCode = parseArguments.checkArguments(argumentsCount,arguments);
    std::string *certificateDirPathReturn = parseArguments.getCertificateDirectoryPath();
    std::string *certificateFilePathReturn = parseArguments.getCertificateFilePath();
    assert(expectedCode == returnCode);

    assert(certificateFilePathReturn == nullptr);

    assert(certificateDirPathReturn != nullptr);
    assert(((*certificateDirPathReturn).compare(certPathReturn)) == 0);
}

void TestArgumentParser::certificateFileNoPathArgument() {
    ParseArguments parseArguments;

    int argumentsCount = 3;
    char *arguments[] = {&programName[0],&urlSting[0],&argumentCertificateFile[0]};

    bool expectedCode = false;


    bool returnCode = parseArguments.checkArguments(argumentsCount,arguments);

    assert(expectedCode == returnCode);
}

void TestArgumentParser::certificateFileArgument() {
    ParseArguments parseArguments;

    int argumentsCount = 4;
    char *arguments[] = {&programName[0], &urlSting[0],
                         &argumentCertificateFile[0], &certificateFilePath[0]};

    bool expectedCode = true;
    std::string certPathReturn = certificateFilePath;


    bool returnCode = parseArguments.checkArguments(argumentsCount,arguments);
    std::string *certificateFilePathReturn = parseArguments.getCertificateFilePath();
    std::string *certificateDirPathReturn = parseArguments.getCertificateDirectoryPath();

    assert(expectedCode == returnCode);

    assert(certificateDirPathReturn == nullptr);

    assert(certificateFilePathReturn != nullptr);
    assert(((*certificateFilePathReturn).compare(certPathReturn)) == 0);
}

void TestArgumentParser::certificateDirAndFileArgument() {
    ParseArguments parseArguments;

    int argumentsCount = 6;
    char *arguments[] = {&programName[0],&urlSting[0],
                         &argumentCertificateFile[0], &certificateFilePath[0],
                         &argumentCertificateDir[0], &certificateDirPath[0]};

    bool expectedCode = true;
    std::string certFilePathReturn = certificateFilePath;
    std::string certDirPathFileReturn = certificateDirPath;


    bool returnCode = parseArguments.checkArguments(argumentsCount,arguments);
    std::string *certificateFilePathReturn = parseArguments.getCertificateFilePath();
    std::string *certificateDirPathReturn = parseArguments.getCertificateDirectoryPath();

    assert(expectedCode == returnCode);

    assert(certificateDirPathReturn != nullptr);
    assert(((*certificateDirPathReturn).compare(certDirPathFileReturn)) == 0);

    assert(certificateFilePathReturn != nullptr);
    assert(((*certificateFilePathReturn).compare(certFilePathReturn)) == 0);
}

void TestArgumentParser::printTimeArgument() {
    ParseArguments parseArguments;

    int argumentsCount = 3;
    char *arguments[] = {&programName[0], &urlSting[0], &argumentTime[0]};

    bool expectedCode = true;


    bool returnCode = parseArguments.checkArguments(argumentsCount,arguments);
    bool isTimeReturn = parseArguments.isTime();
    bool isAuthorReturn = parseArguments.isAuthor();
    bool isAssociateUrlReturn = parseArguments.isAssociateUrl();

    assert(expectedCode == returnCode);

    assert(isTimeReturn == true);
    assert(isAuthorReturn == false);
    assert(isAssociateUrlReturn == false);
}

void TestArgumentParser::printAuthorArgument() {
    ParseArguments parseArguments;

    int argumentsCount = 3;
    char *arguments[] = {&programName[0], &urlSting[0], &argumentAuthor[0]};

    bool expectedCode = true;


    bool returnCode = parseArguments.checkArguments(argumentsCount,arguments);
    bool isTimeReturn = parseArguments.isTime();
    bool isAuthorReturn = parseArguments.isAuthor();
    bool isAssociateUrlReturn = parseArguments.isAssociateUrl();

    assert(expectedCode == returnCode);

    assert(isTimeReturn == false);
    assert(isAuthorReturn == true);
    assert(isAssociateUrlReturn == false);
}

void TestArgumentParser::printUrlArgument() {

    ParseArguments parseArguments;

    int argumentsCount = 3;
    char *arguments[] = {&programName[0], &urlSting[0], &argumentURL[0]};

    bool expectedCode = true;


    bool returnCode = parseArguments.checkArguments(argumentsCount,arguments);
    bool isTimeReturn = parseArguments.isTime();
    bool isAuthorReturn = parseArguments.isAuthor();
    bool isAssociateUrlReturn = parseArguments.isAssociateUrl();

    assert(expectedCode == returnCode);

    assert(isTimeReturn == false);
    assert(isAuthorReturn == false);
    assert(isAssociateUrlReturn == true);


}

void TestArgumentParser::allNormalArguments() {

    ParseArguments parseArguments;

    int argumentsCount = 7;
    char *arguments[] = {&programName[0], &urlSting[0],
                         &argumentCertificateDir[0], &certificateDirPath[0],
                         &argumentTime[0],&argumentAuthor[0],&argumentURL[0]};

    bool expectedCode = true;
    std::string expectUrl = urlSting;
    std::string certPathReturn = certificateDirPath;


    bool returnCode = parseArguments.checkArguments(argumentsCount,arguments);
    std::string *urlReturn = parseArguments.getUrl();
    std::string *feedFilePathReturn = parseArguments.getFeedFilePath();
    std::string *certificateFilePathReturn = parseArguments.getCertificateFilePath();
    std::string *certificateDirPathReturn = parseArguments.getCertificateDirectoryPath();
    bool isTimeReturn = parseArguments.isTime();
    bool isAuthorReturn = parseArguments.isAuthor();
    bool isAssociateUrlReturn = parseArguments.isAssociateUrl();

    assert(expectedCode == returnCode);

    assert(urlReturn != nullptr);
    assert(((*urlReturn).compare(expectUrl)) == 0);

    assert(feedFilePathReturn == nullptr);
    assert(certificateFilePathReturn == nullptr);

    assert(certificateDirPathReturn != nullptr);
    assert(((*certificateDirPathReturn).compare(certPathReturn)) == 0);

    assert(isTimeReturn == true);
    assert(isAuthorReturn == true);
    assert(isAssociateUrlReturn == true);

}
