//
//  main.cpp
//  Practice
//
//  Created by Вадим Кохтев on 05/07/15.
//  Copyright (c) 2015 Вадим Кохтев. All rights reserved.
//

#include "header.h"
#include	<sys/types.h>	/* basic system data types */
#include	<sys/socket.h>	/* basic socket definitions */
#include	<sys/time.h>	/* timeval{} for select() */
#include	<time.h>		/* timespec{} for pselect() */
#include	<netinet/in.h>	/* sockaddr_in{} and other Internet defns */
#include	<arpa/inet.h>	/* inet(3) functions */
#include	<errno.h>
#include	<fcntl.h>		/* for nonblocking */
#include	<netdb.h>
#include	<signal.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<sys/stat.h>	/* for S_xxx file mode constants */
#include	<sys/uio.h>		/* for iovec{} and readv/writev */
#include	<unistd.h>
#include	<sys/wait.h>
#include	<sys/un.h>		/* for Unix domain sockets */

#include <iostream>

#define ERROR -1
#define MAXLINE 1024

struct sockaddr_in server;

int main(int argc, char **argv) {
    int client_sockfd;
    char buff[MAXLINE];
    int sockaddr_len = sizeof(struct sockaddr_in);
    size_t buff_len;
    
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (sockfd == ERROR) {
        std::cerr << "Can't open socket" << std::endl;
        exit(-1);
    }
    
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(50000);
    
    
    
    int connection =  bind(sockfd, (struct sockaddr *)&server, sockaddr_len);
    if (connection == ERROR) {
        perror("errno");
        exit(-1);
    }
    
    
    
    if (listen(sockfd, 10) == ERROR) {
        perror("errno");
        exit(-1);
    }

    
    while (true) {
        client_sockfd = accept(sockfd, NULL, NULL);
        if (client_sockfd == ERROR) {
            std::cerr << "Can't accept" << std::endl;
            exit(-1);
        }
        
        
        
        buff_len = 1;
        while (buff_len != 0) {
            buff_len = read(client_sockfd, buff, MAXLINE);
            write(client_sockfd, buff, buff_len);
        }
        std::cout << "Client disconnected" << std::endl;
        close(client_sockfd);
    }
}
