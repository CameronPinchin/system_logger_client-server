#include "server.h"

void Server::organizeClientData(Logger::sys_info system_information){

    



}

void Server::listenForClient(){
    
    WSADATA wsaData;
    if(WSAStartup(MAKEWORD(2, 2), &wsaData)){
        cout << "[SERVER] WSAStartup failed. " << endl;
        return;
    }


    // creating socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    SOCKET clientSocket;

    // specifying address & port
    sockaddr_in serverAddress, clientAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    int clientSize = sizeof(clientAddress);

    // bind socket
    if(bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR){
        cout << "[SERVER] Failed to bind socket." << endl;
        closesocket(serverSocket);
        WSACleanup();
        return;
    } else {
        cout << "[SERVER] Socket has been bound. " << endl;
    }

    listen(serverSocket, SOMAXCONN);
    cout << "[SERVER] Listening on port 8080. " << endl;

    while(true){
        clientSocket = accept(serverSocket, (sockaddr*)&clientAddress, &clientSize);
        if(clientSocket == INVALID_SOCKET){
            cout << "[SERVER] Failed to accept client. " << endl;
            continue;
        }

        cout << "[SERVER] Successfully accepted client. " << endl;

        Logger::sys_info received_system_info;
        int bytes_received = recv(clientSocket, (char*)&received_system_info, sizeof(received_system_info), 0);
        if(bytes_received > 0){
            cout << "[SERVER] Received message from client. " << endl;
            cout << "[SERVER] CPU Info: " << received_system_info.cpu.num_processors << " Total Processors. " << endl;
        } else {
            cout << "[SERVER] Failed to receive message from client. " << endl;
        }
        closesocket(clientSocket);
        cout << "[SERVER] Client disconnected" << endl;
    }
    
    closesocket(serverSocket);
    WSACleanup();
}

int main(){
    Server server;
    server.listenForClient();
    return 0;
}


