/**
 * Project: Čtečka novinek ve formátu Atom a RSS s podporou TLS
 *
 * File:     Error.h
 * Subject:  ISA 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 */

#ifndef ISA_ERROR_H
#define ISA_ERROR_H
#include <iostream>

/**
 * The class contains methods for displaying errors.
 */
class Error {

public:
    enum {
        ERROR_ARGUMENT_NOT_EXIST =  100,
        ERROR_ARGUMENT_NOT_VALUE = 101,
        ERROR_URL_OR_FEED_FILE = 102,
        ERROR_ARGUMENT_REPEAT = 103,

        ERROR_ARGUMENT = 103,

        ERROR_FAIL_DEFAULT_CERTIFICATE = 110,
        ERROR_FAIL_CERTIFICATE_FILE = 111,
        ERROR_FAIL_CERTIFICATE_DIR = 112,
        ERROR_FAIL_OPEN_SECURE_CONNECT = 113,
        ERROR_FAIL_OPEN_CONNECT = 114,
        ERROR_FAIL_CREATE_BIO = 115,
        ERROR_SEND_REQUEST = 116,

        ERROR_CERTIFICATE_INVALID = 120,
        ERROR_SSL_CONNECTION_FAIL = 121,
        ERROR_READ_BIO = 122,
        ERROR_SSL = 123,

        ERROR_URL_INVALID = 130,
        ERROR_PORT_INVALID = 131,

        ERROR_NOT_OPEN_XML_DOC = 140,
        ERROR_NOT_EXIST_ROOT_ELEMENT = 141,
        ERROR_NOT_SUPPORTED_FORMAT = 142,
        ERROR_NOT_SUPPORTED_RSS_VERSION =143,

        ERROR_NOT_CORRECT_RESPONSE = 150,
        ERROR_RESPONSE_HAS_NO_BODY = 151,

        ERROR_NOT_OPEN_FILE = 160,


    };

    enum{
        SUCCESS = 0,
        EXIT_FAIL = 1,
    };

    static void errorPrint(int errorNumber);
    static void printMessage(std::string message);
    static void exitProgram(int exitNumber);
    static void helpOut();

};


#endif //ISA_ERROR_H
