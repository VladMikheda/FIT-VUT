/**
 * Project: Vytvoření serveru komunikujícího prostřednictvím protokolu HTTP
 *
 * File:     main.cpp
 * Subject:  IPK 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 */

#include "Server.h"
#include <cstdlib>
using namespace std;

/**
 * function checks the correctness of the entered arguments
 * @param argc
 * @param argv
 * @param port
 */
void argument(int argc, char **argv, int* port){
    if(argc != 2){
        std::cerr << "ERROR: Port not specified" << std::endl;
        exit(ERROR_PORT);
    }
    if(argv[1][0] == '+'){
        std::cerr << "ERROR: The port is incorrect or not specified" << std::endl;
        std::cerr << "start program: \n .\\hinfosvc <port>" << std::endl;
        exit(ERROR_PORT);
    }
    try{
        *port = stoi(argv[1],nullptr,10);
    }
    catch(exception const& e ) {
        std::cerr << "ERROR: The port is incorrect or not specified" << std::endl;
        std::cerr << "start program: \n .\\hinfosvc <port>" << std::endl;
        exit(ERROR_PORT);
    }

    if(*port == 0 || *port > 65535 || *port < 1){
        std::cerr << "ERROR: The port is incorrect or not specified" << std::endl;
        std::cerr << "start program: \n .\\hinfosvc <port>" << std::endl;
        exit(ERROR_PORT);
    }
}


/**
 * main function program,
 * starts the server and forwards the port
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char **argv) {
    int port = 0;
    argument(argc,argv,&port);

    Server server(port);
    server.server_start();

    return 0;
}
