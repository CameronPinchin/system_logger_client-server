#ifndef SERVER_H
#define SERVER_H

#include <Winsock2.h>
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <ctime>
#include "sys_logger.h"
#include "json.h"

using namespace std;

class Server {
    public:
        void listenForClient();
        void organizeClientData(Logger::sys_info &system_information);
};

#endif