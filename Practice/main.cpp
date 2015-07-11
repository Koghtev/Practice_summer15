//
//  main.cpp
//  Practice
//
//  Created by Вадим Кохтев on 05/07/15.
//  Copyright (c) 2015 Вадим Кохтев. All rights reserved.
//

#include "header.h"

#define ERROR -1
#define MAXLINE 1024

struct sockaddr_in server;

int main(int argc, char **argv) {
    
    
    Server server(EchoHandler, 50000);
    server.start();
    sleep(10);
    
    server.stop();
}
