//
// Created by magshimim on 13-Dec-22.
//
#include "APICommunicator.h"
std::string getIpData(std::string ip) {
    int sock;
    struct sockaddr_in client;
    int PORT = 80;
    struct hostent * host = gethostbyname("ip-api.com");

    if ( (host == NULL) || (host->h_addr == NULL) ) {
        throw std::runtime_error("error retreiving dns data");
    }
    bzero(&client, sizeof(client));
    client.sin_family = AF_INET;
    client.sin_port = htons( PORT );
    memcpy(&client.sin_addr, host->h_addr, host->h_length);
    if (sock < 0) {
        throw std::runtime_error("error creating socket");
    }
    if ( connect(sock, (struct sockaddr *)&client, sizeof(client)) < 0 ) {
        close(sock);
        throw std::runtime_error("could not connect");
    }
    std::stringstream ss;
    ss << "GET /json/" << ip << "fields=60957 HTTP/1.1\r\n"
    << "Host: ip-api.com\r\n"
    << "Accept: application/json\r\n"
    << "\r\n\r\n";
    std::string request = ss.str();
    if (send(sock, request.c_str(), request.length(), 0) != (int)request.length()) {
        throw std::runtime_error("could not send");
    }
    int n;
    std::string raw_site;
    char buffer[4096];
    while ((n = recv(sock, buffer, sizeof(buffer), 0)) > 0){
        raw_site.append(buffer, n);
    }
    close(sock);
    return raw_site;
}
