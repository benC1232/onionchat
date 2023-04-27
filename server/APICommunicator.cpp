//
// Created by magshimim on 13-Dec-22.
//
#include "APICommunicator.h"
IpData getIpData(std::string ip) {
    //this is for testing on localhost
    if(ip == "127.0.0.1")
    {
        ip = "1.1.1.1";
    }

    int sock = socket(AF_INET, SOCK_STREAM, 0);;
    struct sockaddr_in client;
    int PORT = 80;
    bzero(&client, sizeof(client));
    client.sin_family = AF_INET;
    client.sin_port = htons( PORT );
    client.sin_addr.s_addr = inet_addr("208.95.112.1");
    if (sock < 0) {
        throw std::runtime_error("error creating socket");
    }
    if ( connect(sock, (struct sockaddr *)&client, sizeof(client)) < 0 ) {
        close(sock);
        throw std::runtime_error("could not connect");
    }
    std::stringstream ss;
    ss << "GET /json/" << ip << "?fields=1073689 HTTP/1.1\r\n"
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
    n = recv(sock, buffer, sizeof(buffer), 0);
    raw_site.append(buffer, n);
    close(sock);

    return JsonRequestPacketDeserializer::deserializeIpData(getResponseBody(raw_site));
}
//used this https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
std::string getResponseBody(std::string response) {
    size_t body = response.find("\r\n\r\n");
    if (body == std::string::npos) {
        return "";
    }
    return response.substr(body + 4);
}
