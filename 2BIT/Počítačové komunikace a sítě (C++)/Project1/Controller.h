/**
 * Project: Vytvoření serveru komunikujícího prostřednictvím protokolu HTTP
 *
 * File:     Controller.h
 * Subject:  IPK 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 */

#ifndef IPK_PROJ1CPP_CONTROLER_H
#define IPK_PROJ1CPP_CONTROLER_H


#include <unistd.h>
#include <fstream>
#include "HttpRequest.h"
#include "HTTPResponse.h"
#include "ServerInfo.h"


class Controller{
private:

    enum{METHOD_NUMBER = 6};
    string METHOD[METHOD_NUMBER];

    HTTPResponse page_hostname(HttpRequest& request, HTTPResponse& response);
    HTTPResponse page_cpuname(HttpRequest& request, HTTPResponse& response);
    HTTPResponse page_load(HttpRequest& request, HTTPResponse& response);
    HTTPResponse page_notfound(HTTPResponse& response);
    HTTPResponse method_not_valid(HTTPResponse& response);
    HTTPResponse method_not_allowed(HTTPResponse& response);
    HTTPResponse not_content(HTTPResponse& response);
    HTTPResponse conflict(HTTPResponse& response);

public:
    Controller();
    HTTPResponse selection(HttpRequest request);


};


#endif //IPK_PROJ1CPP_CONTROLER_H
