/**
 * Project: Čtečka novinek ve formátu Atom a RSS s podporou TLS (Tests)
 *
 * File:     TestConnect.h
 * Subject:  ISA 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 */




#ifndef ISA_TESTCONNECT_H
#define ISA_TESTCONNECT_H


#include <string>
#include "../../Connect.h"

/**
 * Unit test suite class for connection testing
 */
class TestConnect {

private:
    const std::string domainHTTP = "info.cern.ch:80";
    const std::string domainHTTPSPort = "httpbin.org:443";
    const std::string domainHTTPS = "httpbin.org";
    std::string requestHTTPS = "GET /ip HTTP/1.0\r\nHost:httpbin.org\r\nConnection:Close\r\nUser-Agent:Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/51.0.2704.103 Safari/537.36\r\n\r\n";


    std::string requestHTTP = "GET / HTTP/1.0\r\nHost:info.cern.ch\r\nConnection:Close\r\nUser-Agent:Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/51.0.2704.103 Safari/537.36\r\n\r\n";

public:
    void connectHTTP();
    void connectDefaultHTTPS();
    void connectCertFileHTTPS();
    void connectCertDirHTTPS();
    void connectCertFileAndDirHTTPS();
    void twoConnect();
};


#endif //ISA_TESTCONNECT_H
