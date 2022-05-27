/**
 * Project: Vytvoření serveru komunikujícího prostřednictvím protokolu HTTP
 *
 * File:     Server.cpp
 * Subject:  IPK 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 */

#include "Server.h"


 Server::Server(int p){
    port = p;
}

/**
 * server start
 * open socket
 * create server socket
 * bind the socket to our specified IP and port
 * listening
 */
 void Server::server_start(){
    server.set_port(port);
    server.set_domian(AF_INET);
    server.set_type(SOCK_STREAM);
    server.set_sin_addr(AF_INET,INADDR_ANY);
    server.Socket();
    server.Bind();
    server.Listen();

    Controller controller;
    HttpRequest request;
    char buffer[BUFFER_SIZE] = {0};
    int socket_desk;

    //server main loop
    while(true){
        socket_desk = server.Accept();
        while(true){ //request read loop
            memset(buffer,'\0', sizeof(buffer));
            int buffer_real_size = (int) read(socket_desk, buffer, BUFFER_SIZE-1);
            buffer[buffer_real_size++] = '\0';
            req_str.append(buffer);

            if (buffer_real_size < BUFFER_SIZE) {
                break;
            }
        }

        request.set_all(req_str);

        string response_str = controller.selection(request).get_resp_mess();

        //write response
        write(socket_desk,response_str.data(),response_str.size());
        close(socket_desk);

        request.clear_all();
        req_str.clear();
    }

}
