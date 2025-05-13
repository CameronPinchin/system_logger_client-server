#include "sys_logger_client.h"
#include "sys_logger.h"

using namespace std;

void Client::sendLogToServer(){

    // This is needed on windows:
    WSADATA wsaData;

    if(WSAStartup(MAKEWORD(2, 2), &wsaData)){
        cout << "[CLIENT] WSAStartup failed. " << endl;
        return;
    }
    
    SOCKET clientSocket;
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1"); 

    while(true){
        clientSocket = socket(AF_INET, SOCK_STREAM, 0);
        if(clientSocket == INVALID_SOCKET){
            cout << "[CLIENT] Failed to create socket. " << endl;
            return;
        }

        cout << "[CLIENT] Trying to connect to server... " << endl;
        if(connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) != SOCKET_ERROR){
            cout << "[CLIENT] Connected to server. " << endl;
            break;
        } else {
            cout << "[CLIENT] Connection failed. Retrying in 2 seconds. " << endl;
            closesocket(clientSocket);
            this_thread::sleep_for(chrono::seconds(2));
        }
    }


    Logger logger;
    Logger::sys_info system_information = logger.getAllSysInfo();
    send(clientSocket, (char*)&system_information, sizeof(system_information), 0);
    cout << "[CLIENT] Message sent to server. " << endl;
    
    closesocket(clientSocket);
    WSACleanup();
}

int main(){
    Client client;
    client.sendLogToServer();
    return 0;
}




