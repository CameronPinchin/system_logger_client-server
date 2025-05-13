#ifndef SYS_LOGGER_CLIENT_H
#define SYS_LOGGER_CLIENT_H

#include <iostream>
#include <Winsock2.h>
#include <Windows.h>
#include <thread>
#include <chrono>
#include "sys_logger.h"
#include "server.h"

using namespace std;

class Client {
    public:

        void sendLogToServer();
        

};

#endif