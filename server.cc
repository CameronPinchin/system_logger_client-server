#include "server.h"

void Server::organizeClientData(Logger::sys_info &system_information){

    ofstream myfile;
    myfile.open("logfile.csv", ios::app);

    cout << "[SERVER] Opened 'logfile.csv'" << endl;

    myfile << "\n";
    myfile << "Log Timestamp: " << system_information.log_time << "\n";
    myfile << "CPU Data: \n";
    myfile << "Number of Processors, OEM ID, Page Size (KB), Processor Mask, Processor Type \n";
    myfile <<  system_information.cpu.num_processors << ",";
    myfile <<  system_information.cpu.oem_id << ",";
    myfile <<  system_information.cpu.page_size << ",";
    myfile <<  system_information.cpu.processor_mask << ",";
    myfile <<  system_information.cpu.processor_type;
    myfile << "\n";
    
    myfile << "Memory Data: \n";
    myfile << "Current Usage, Total Physical Memory, Available Physical Memory, Total Virtual Memory, Available Virtual Memory \n";
    myfile << system_information.mem.current_mem_load << ",";
    myfile << system_information.mem.total_phys_mem << ",";
    myfile << system_information.mem.avail_phys_mem << ",";
    myfile << system_information.mem.total_virt_mem << ",";
    myfile << system_information.mem.avail_virt_mem;
    myfile << "\n";

    myfile << "Disk Data: \n";
    myfile << "Total Storage (GB), Available Storage (GB), Free Storage(GB) \n";
    myfile << system_information.dsk.total_bytes << ",";
    myfile << system_information.dsk.avail_bytes << ",";
    myfile << system_information.dsk.total_free_bytes;
    myfile << "\n";

    myfile << "semi;colon \n";
    
    cout << "[SERVER] Closing 'logfile.csv'" << endl;

    myfile.close();
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
            cout << "[SERVER] Received log data, organizing to file." << endl;
            organizeClientData(received_system_info);
            cout << "[SERVER] Successfully edited 'logfile.csv'." << endl;
        } else {
            cout << "[SERVER] Failed to receive message from client. " << endl;
        }
        closesocket(clientSocket);
        cout << "[SERVER] Client disconnected" << endl;
    }
    
    cout << "[SERVER] Closing socket. " << endl;
    closesocket(serverSocket);
    WSACleanup();
}

int main(){
    Server server;
    server.listenForClient();
    return 0;
}


