/**
 * Project: Vytvoření serveru komunikujícího prostřednictvím protokolu HTTP
 *
 * File:     HTTPRequest.h
 * Subject:  IPK 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 */

#include "HttpRequest.h"

/**
 * parse the request to:
 *      method,
 *      url,
 *      protocol
 */
 void HttpRequest::set_all(string req){
     error_request = false;
     req_mess = req;

     string part;
     part = req_mess.substr(0, req_mess.find("\r\n\r\n"));

     string line;
     line = part.substr(0,part.find('\n'));

     int pos_first_sub = (int)part.find(' ');
     int pos_sec_sub = (int)part.find(' ', pos_first_sub + 1);
     int len_to_sec_sub = (int)pos_sec_sub - (pos_first_sub + 1);
     int pos_sec_slash = (int)part.find('/', pos_sec_sub + 1);
     int len_to_sec_slash = (int)pos_sec_slash - (pos_sec_sub + 1);
     int pos_first_lb = (int)part.find('\n');

     method = line.substr(0,pos_first_sub);
     url = line.substr(pos_first_sub + 1, len_to_sec_sub);
     protocol = line.substr(pos_sec_sub + 1, len_to_sec_slash);
     if(protocol != "HTTP"){
         error_request = true;
     }
     protocol_version = line.substr(pos_sec_slash + 1, pos_first_lb);

     if(!(protocol_version == "1.1\r" || protocol_version == "1.0\r" || protocol_version == "0.9\r" || protocol_version == "2\r")){
         error_request = true;
     }
}
 string HttpRequest::get_method(){
    return method;
}
 string HttpRequest::get_url(){
    return url;
}
 string HttpRequest::get_protocol(){
    return protocol;
}
 string HttpRequest::get_protocol_version(){
    return protocol_version;
}

bool HttpRequest::get_error_request() const{
    return error_request;
 }
void HttpRequest::clear_all(){
     req_mess.clear();
     method.clear();
     protocol.clear();
     protocol_version.clear();
     url.clear();
}
