/**
 * Project: Čtečka novinek ve formátu Atom a RSS s podporou TLS (Tests)
 *
 * File:     TestConnect.cpp
 * Subject:  ISA 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 */




#include <cassert>
#include "TestConnect.h"


void TestConnect::connectHTTP() {
    Connect connect;
    connect.initialization();

    bool returnConnect = connect.insecureConnect(domainHTTP);
    assert(returnConnect == true);
    bool returnCheck = connect.checkConnect();
    assert(returnCheck == true);


    bool returnRequest = connect.sendRequest(requestHTTP);

    assert(returnRequest == true);

    std::string response = "";
    bool returnResponse = connect.readResponse(response);
    assert(returnResponse == true);
    assert(response.empty() == false);

    connect.closeConnect();


}

void TestConnect::connectDefaultHTTPS() {

    Connect connect;
    connect.initialization();

    connect.initializationSslConnect();

    bool returnCert = connect.addDefaultSslCertificate();
    assert(returnCert == true);

    bool returnBio = connect.settingBio();
    assert(returnBio == true);

    bool returnSslConnect = connect.sslConnect(domainHTTPSPort,domainHTTPS);
    assert(returnSslConnect == true);

    bool returnCheck = connect.checkConnect();
    assert(returnCheck == true);

    bool returnValid = connect.isCertificateValid();
    assert(returnValid == true);

    bool returnRequest = connect.sendRequest(requestHTTPS);
    assert(returnRequest == true);

    std::string response = "";
    bool returnResponse = connect.readResponse(response);
    assert(returnResponse == true);
    assert(response.empty() == false);

    connect.closeConnect();

//    std::cout << response << std::endl;

}

void TestConnect::connectCertFileHTTPS() {
    Connect connect;
    connect.initialization();

    connect.initializationSslConnect();

    bool returnCert = connect.addSslCertificate("/etc/ssl/certs/Amazon_Root_CA_1.pem");
    assert(returnCert == true);

    bool returnBio = connect.settingBio();
    assert(returnBio == true);

    bool returnSslConnect = connect.sslConnect(domainHTTPSPort,domainHTTPS);
    assert(returnSslConnect == true);

    bool returnCheck = connect.checkConnect();
    assert(returnCheck == true);

    bool returnValid = connect.isCertificateValid();
    assert(returnValid == true);

    bool returnRequest = connect.sendRequest(requestHTTPS);
    assert(returnRequest == true);

    std::string response = "";
    bool returnResponse = connect.readResponse(response);
    assert(returnResponse == true);
    assert(response.empty() == false);

    connect.closeConnect();
}

void TestConnect::connectCertDirHTTPS() {
    Connect connect;
    connect.initialization();

    connect.initializationSslConnect();

    bool returnCert = connect.addSslCertificateDir("/etc/ssl/certs");
    assert(returnCert == true);

    bool returnBio = connect.settingBio();
    assert(returnBio == true);

    bool returnSslConnect = connect.sslConnect(domainHTTPSPort,domainHTTPS);
    assert(returnSslConnect == true);

    bool returnCheck = connect.checkConnect();
    assert(returnCheck == true);

    bool returnValid = connect.isCertificateValid();
    assert(returnValid == true);

    bool returnRequest = connect.sendRequest(requestHTTPS);
    assert(returnRequest == true);

    std::string response = "";
    bool returnResponse = connect.readResponse(response);
    assert(returnResponse == true);
    assert(response.empty() == false);

    connect.closeConnect();
}

void TestConnect::connectCertFileAndDirHTTPS() {
    Connect connect;
    connect.initialization();

    connect.initializationSslConnect();

    bool returnCert = connect.addSslCertificateAndDir("/etc/ssl/certs/Amazon_Root_CA_1.pem","/etc/ssl/certs");
    assert(returnCert == true);

    bool returnBio = connect.settingBio();
    assert(returnBio == true);

    bool returnSslConnect = connect.sslConnect(domainHTTPSPort,domainHTTPS);
    assert(returnSslConnect == true);

    bool returnCheck = connect.checkConnect();
    assert(returnCheck == true);

    bool returnValid = connect.isCertificateValid();
    assert(returnValid == true);

    bool returnRequest = connect.sendRequest(requestHTTPS);
    assert(returnRequest == true);

    std::string response = "";
    bool returnResponse = connect.readResponse(response);
    assert(returnResponse == true);
    assert(response.empty() == false);

    connect.closeConnect();
}

void TestConnect::twoConnect() {
    Connect connect;
    connect.initialization();

    bool returnConnect = connect.insecureConnect(domainHTTP);
    assert(returnConnect == true);
    bool returnCheck = connect.checkConnect();
    assert(returnCheck == true);


    bool returnRequest = connect.sendRequest(requestHTTP);

    assert(returnRequest == true);

    std::string response = "";
    bool returnResponse = connect.readResponse(response);
    assert(returnResponse == true);
    assert(response.empty() == false);

    connect.closeConnect();

    connect.initializationSslConnect();

    bool returnCert = connect.addDefaultSslCertificate();
    assert(returnCert == true);

    bool returnBio = connect.settingBio();
    assert(returnBio == true);

    bool returnSslConnect = connect.sslConnect(domainHTTPSPort,domainHTTPS);
    assert(returnSslConnect == true);

    returnCheck = connect.checkConnect();
    assert(returnCheck == true);

    bool returnValid = connect.isCertificateValid();
    assert(returnValid == true);

    returnRequest = connect.sendRequest(requestHTTPS);
    assert(returnRequest == true);

    response = "";
    returnResponse = connect.readResponse(response);
    assert(returnResponse == true);
    assert(response.empty() == false);

    connect.closeConnect();

}
