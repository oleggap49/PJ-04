#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include"User.h"
 
using namespace std;

#define MESSAGE_LENGTH 1024 // ћаксимальный размер буфера дл€ данных
#define LOGIN_LENGTH 8      // размер буфера под логин в Message c 1 по 8 байт
#define PASS_LENGTH  8      // размер буфера под логин в Message c 9 по 15 байт
#define PORT 7777 //   номер порта



class Chat
{
public:
    Chat()
    {
        users.emplace_back("admin", "admin", true);
    }

    ~Chat() {}
    void StartTCPServer();
    int TCPServerDialogue();
     
    
   bool Registration();
    bool Autorisation();
    void UsersList();
    bool SearchNick(const string& lgn);
    bool SendMessage();
    void ReadLog();


private:
    struct sockaddr_in serveraddress, client;
    socklen_t length;
    int socket_file_descriptor, connection, bind_status, connection_status;
    char message[MESSAGE_LENGTH];                  // сообщение от клиента 0 - команда 1-8 - логин 9-16 - пароль 17-1023 - техт


    vector<User> users;     // зарегистрированные пользователи
    list<Message> logMsg;  // журнал
};

