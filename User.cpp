#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "User.h"
using namespace std;

void User::StartTCPClient()
{
    socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_file_descriptor == -1) {
        cout << "Creation of Socket failed!" << endl;
        exit(1);
    }

    // Установим адрес сервера
    serveraddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    // Зададим номер порта
    serveraddress.sin_port = htons(PORT);
    // Используем IPv4
    serveraddress.sin_family = AF_INET;
    // Установим соединение с сервером
    connection = connect(socket_file_descriptor, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
    if (connection == -1) {
        cout << "Connection with the server failed.!" << endl;
        exit(1);
    }
}
int User::TCPClientDialogue()
{
    while (1)
   {
           // take a prompt
              bzero(message, sizeof(message));
               read(socket_file_descriptor, message, sizeof(message));
              cout << " from server: \n" << message << endl;
             // enter from console
             bzero(message, sizeof(message));
               cin >> message;

           if ((strncmp(message, "end", 3)) == 0) 
            {
            write(socket_file_descriptor, message, sizeof(message));
            cout << "Client Exit." << endl;
            break;
            }
                    // send to server
                    ssize_t bytes = write(socket_file_descriptor, message, sizeof(message));
                    if (bytes >= 0) 
                    {
                    //  cout << "Data send to the server successfully.!" << endl;
                     }

        
                   
        
    } 
    
    close(socket_file_descriptor);
    return 0;
}

