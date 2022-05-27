/**
 * Project: Vytvoření serveru komunikujícího prostřednictvím protokolu HTTP
 *
 * File:     Tcp.h
 * Subject:  IPK 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 */

#ifndef IPK_PROJ1CPP_TCP_H
#define IPK_PROJ1CPP_TCP_H

#include <sys/socket.h>
#include "error.h"
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/un.h>

class Tcp {
private:
    int port;
    int server;
    int domian;
    int type;
    struct sockaddr_in addr;

public:
    void set_port(int value);
    int get_port() const;
    void set_domian(int value);
    void set_type(int value);
    void set_sin_addr(int family,int sin_addr);
    void Socket();
    void Bind();
    void Listen() const;
    int Accept() const;

};


#endif //IPK_PROJ1CPP_TCP_H
