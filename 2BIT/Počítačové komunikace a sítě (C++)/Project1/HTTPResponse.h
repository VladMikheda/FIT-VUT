/**
 * Project: Vytvoření serveru komunikujícího prostřednictvím protokolu HTTP
 *
 * File:     HTTPResponse.h
 * Subject:  IPK 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 */

#ifndef IPK_PROJ1CPP_HTTPRESPONSE_H
#define IPK_PROJ1CPP_HTTPRESPONSE_H
#include <iostream>
using namespace std;

class HTTPResponse{

    enum e_heders{
        protocol = 0,
        content_type,
        content_length,
        connection
    };

    enum {
        HEADERS_NUMBER = 5
    };
private:
    string headers[HEADERS_NUMBER];
    string body;
    string resp_mess;

public:
    HTTPResponse();
    void set_code(const string& code);
    void set_status(const string& status);
//    void set_server_name(string server_name);
    void set_content_type(const string& content_type);
    void set_connection(const string& connection);
    void set_body(const string& body_str);
    void create_resp_mess();
    string get_resp_mess();

};


#endif //IPK_PROJ1CPP_HTTPRESPONSE_H
