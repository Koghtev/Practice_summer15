//
//  Header.h
//  Practice
//
//  Created by Вадим Кохтев on 06/07/15.
//  Copyright (c) 2015 Вадим Кохтев. All rights reserved.
//

#ifndef Practice_Header_h
#define Practice_Header_h

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
#include <atomic>
#include <poll.h>
#include <thread>
#include <functional>


#define ERROR -1
#define MAXLINE 1024

void EchoHandler(int socket) {
    size_t buff_len;
    char buff[MAXLINE];
    buff_len = 1;
    while (buff_len != 0) {
        buff_len = read(socket, buff, MAXLINE);
        write(socket, buff, buff_len);
    }
    // echo (read write)
}

void NullHandler(int socket) {
    
}

void HTTPHandler(int socket) {
    
}


class Server {
public:
    Server(std::function<void(int)> handler, int port) : run_(true), sockfd(socket(AF_INET, SOCK_STREAM, 0)) {}
    
    void start() {
        // create socket
        // bind, listen
        
        struct sockaddr_in server;
        std::atomic<bool> run_(true);
        
        
        int sockaddr_len = sizeof(struct sockaddr_in);
        
        
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
        
        accept_thread_ = std::thread(&Server::run, this);
    }
    
    void stop() {
        run_ = false;
        accept_thread_.join();
        std::cout << "Client disconnected" << std::endl;
    }
    
private:
    std::atomic<bool> run_;
    std::thread accept_thread_;
    int sockfd;
    
    
    void run() {
        
        struct pollfd poll_;
        poll_.fd = sockfd;
        poll_.events = POLLIN;
        
        int client_sockfd;
        
        while (run_) {
            if (poll(&poll_, 1, 50) == 1){
                client_sockfd = accept(sockfd, NULL, NULL);
                if (client_sockfd == ERROR) {
                    std::cerr << "Can't accept" << std::endl;
                    exit(-1);
                }
                EchoHandler(client_sockfd);
                close(client_sockfd);
            }
        }
        
        
        // while(run)
        //    if(poll)
        //        fd = accept()
        //        handler_(fd)
        //        close(fd)
    }
};


#endif

