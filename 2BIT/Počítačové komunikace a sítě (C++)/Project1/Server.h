/**
 * Project: Vytvoření serveru komunikujícího prostřednictvím protokolu HTTP
 *
 * File:     Server.h
 * Subject:  IPK 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 */

#ifndef IPK_PROJ1CPP_SERVER_H
#define IPK_PROJ1CPP_SERVER_H
#include "Tcp.h"
#include <iostream>
#include <unistd.h>
#include <fstream>
#include "Controller.h"
using namespace std;

class Server{
private:
    enum{ BUFFER_SIZE = 256};
    int port;
    string req_str;
    Tcp server;

public:
    explicit Server(int p);

    void server_start();
};


#endif //IPK_PROJ1CPP_SERVER_H
