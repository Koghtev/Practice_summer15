//
//  server_test.cpp
//  Practice
//
//  Created by Вадим Кохтев on 06/07/15.
//  Copyright (c) 2015 Вадим Кохтев. All rights reserved.
//

#include "gtest/gtest.h"
#include "header.h"
#include <thread>

TEST(Server, Empty) {
    int a = 1;
    int b = 2;
    ASSERT_EQ(a+1, b);
}

TEST(Server, Test_class) {
    Server server(50000);
    server.start();
    server.stop();
    
}

void test_thread(){
    usleep(300);
    std::cout << "b";
    usleep(300);
    std::cout << "d";
}

TEST(Server, Threads) {
    std::thread t1(test_thread);
    std::cout << "a";
    usleep(500);
    std::cout << "c";

    t1.join();
}