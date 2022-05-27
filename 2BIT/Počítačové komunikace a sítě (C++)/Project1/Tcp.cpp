/**
 * Project: Vytvoření serveru komunikujícího prostřednictvím protokolu HTTP
 *
 * File:     Tcp.cpp
 * Subject:  IPK 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 */



/**
 * sketch library socket.h
 */

#include <unistd.h>
#include "Tcp.h"

void Tcp::set_port(int value){
    port = value;
}

int Tcp::get_port() const{
    return port;
}
void Tcp::set_domian(int value){
    domian = value;
}

void Tcp::set_type(int value){
    type = value;
}

void Tcp::set_sin_addr(int family, int sin_addr){
    addr.sin_family = family;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = sin_addr;
}


void Tcp::Socket(){
    server = socket(domian,type,0);
    if(server < 0){
        std::cerr << "ERROR: socket not create" << std::endl;
        exit(ERROR_CREATE_SOCET);
    }
    int a = 1;
    if(0 > setsockopt(server, SOL_SOCKET, SO_REUSEADDR,&a, sizeof(int))){
        exit(ERROR_SETSOCKETOPT);
    }
}

void Tcp::Bind(){
    if(bind(server,(const struct sockaddr *) &addr,sizeof(addr)) < 0){
        close(server);
        std::cerr << "ERROR: the socket was not bound" << std::endl;
        exit(ERROR_BIND);
    }
}

void Tcp::Listen() const{
    if(listen(server,SOMAXCONN) < 0){
        close(server);//?
        std::cerr << "ERROR: listening error" << std::endl;
        exit(ERROR_LISTEN);
    }
}
int Tcp::Accept() const{
    int socket_desk = accept(server, nullptr, nullptr);
    if(socket_desk < 0){
        std::cerr << "ERROR: accept error" << std::endl;
        close(server);
        exit(ERROR_ACCEPT);
    }
    return socket_desk;
}
