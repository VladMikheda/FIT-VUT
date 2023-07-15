/**
 * Project: Čtečka novinek ve formátu Atom a RSS s podporou TLS
 *
 * File:     Connect.h
 * Subject:  ISA 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 */
#ifndef ISA_CONNECT_H
#define ISA_CONNECT_H

# include  "openssl/bio.h"
# include  "openssl/ssl.h"
# include  "openssl/err.h"
#include <string>
#include <iostream>
#include <cstring>
#include "Error.h"
#define BUFFER_SIZE 1024


/**
 * The class is used as a wrapper over the library OpenSSL
 */
class Connect {
public:
    void initialization();
    void initializationSslConnect();

    bool addDefaultSslCertificate();
    bool addSslCertificate(const std::string& certificatePath);
    bool addSslCertificateDir(const std::string& certificateDirPath);
    bool addSslCertificateAndDir(const std::string& certificatePath, const std::string& certificateDirPath);


    bool settingBio();
    bool insecureConnect(const std::string& url);
    bool sslConnect(const std::string& url, const std::string& host);
    bool isCertificateValid();
    bool sendRequest(const std::string& request);
    bool readResponse(std::string &response);
    bool checkConnect();
    void closeConnect();
    void fullExit();


private:
    BIO* bio = nullptr;
    SSL* ssl = nullptr;
    SSL_CTX  *ctx = nullptr;
};


#endif //ISA_CONNECT_H
