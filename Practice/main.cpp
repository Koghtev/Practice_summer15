//
//  main.cpp
//  Practice
//
//  Created by Вадим Кохтев on 05/07/15.
//  Copyright (c) 2015 Вадим Кохтев. All rights reserved.
//

#include "header.h"
#include <iostream>

#define ERROR -1
#define MAXLINE 1024

struct sockaddr_in server,client;

int main(int argc, char **argv) {
    int sockfd, client_sockfd;
    char buff[MAXLINE];
    int sockaddr_len = sizeof(struct sockaddr_in);
    int buff_len;
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (sockfd == ERROR) {
        std::cerr << "Can't open socket" << std::endl;
        exit(-1);
    }
    
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(atoi(argv[1]));
    
    bzero(&server.sin_zero, 80);
    
    int connection =  bind(sockfd, (struct sockaddr *)&server, sockaddr_len);
    if (connection == ERROR) {
        std::cerr << "Can't bind" << std::endl;
        exit(-1);
    }
    int voice = listen(sockfd, 80);
    
    while (voice != 0) {
        client_sockfd = accept(sockfd, NULL, NULL);
        if (client_sockfd == ERROR) {
            std::cerr << "Can't accept" << std::endl;
            exit(-1);
        }
        
        std::cout << "Port" << ntohs(client.sin_port) << "IP" << inet_ntoa(client.sin_addr) << std::endl;
        
        buff_len = 1;
        while (buff_len != 0) {
            buff_len = read(client_sockfd, buff, MAXLINE);
            write(client_sockfd, buff, buff_len);
        }
        std::cout << "Client disconnected" << std::endl;
        close(client_sockfd);
    }
    
}
