#include "mpconnector.h"
#include <iostream>
#include <stdlib.h>
#include <sstream>

MPConnector::MPConnector()
{
    WSADATA data;
    int result;

    result = WSAStartup(MAKEWORD(2,2), &data);
    if (result != 0) {
        std::cerr << "WSAStartup failed: " << result << std::endl;
        exit(EXIT_FAILURE);
    }

    this->socket = INVALID_SOCKET;
}


MPConnector::~MPConnector()
{
    if(socket != INVALID_SOCKET)
        closesocket(this->socket);
    WSACleanup();
}

void MPConnector::connect(const char *serverName, int port) throw (std::exception) {
    if(socket != INVALID_SOCKET)
        closesocket(this->socket);

    // Get server address
    struct hostent *server = NULL;
    server = gethostbyname(serverName);
    if (!server){
        std::stringstream ss;
        ss << "Server "<< serverName << " not found [" << WSAGetLastError() <<"]";
        throw std::exception(ss.str().c_str());
    }

    sockaddr_in serverAddress;
    std::memset((char *)&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    std::memcpy((void *)&serverAddress.sin_addr, server->h_addr_list[0], server->h_length);
    serverAddress.sin_port = htons(port);

    this->socket = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (this->socket == INVALID_SOCKET){
        std::stringstream ss;
        ss << "Cannot allocate socket [" << WSAGetLastError() <<"]";
        throw std::exception(ss.str().c_str());
    }

    if(::connect(socket, (struct sockaddr*) &serverAddress, sizeof(serverAddress)) != 0){
        std::stringstream ss;
        ss << "Cannot connect socket at " << port << " [" << WSAGetLastError() <<"]";
        closesocket(socket);
        throw std::exception(ss.str().c_str());
    }
}

struct MPConnector::MPData MPConnector::getData() throw (std::exception){
    MPData data;
    if(socket != INVALID_SOCKET){
        char request = '!'; // Can be anything
        if(send(socket, &request, 1, NULL) == SOCKET_ERROR){
            std::stringstream ss;
            ss << "Cannot send packet [" << WSAGetLastError() <<"]";
            throw std::exception(ss.str().c_str());
        }


        if(recv(socket, (char*) &data, sizeof(MPData), NULL) == SOCKET_ERROR){
            std::stringstream ss;
            ss << "Cannot recv packet [" << WSAGetLastError() <<"]";
            throw std::exception(ss.str().c_str());
        }
    }
    return data;
}
