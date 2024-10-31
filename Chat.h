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

#define MESSAGE_LENGTH 1024 // ������������ ������ ������ ��� ������
#define LOGIN_LENGTH 8      // ������ ������ ��� ����� � Message c 1 �� 8 ����
#define PASS_LENGTH  8      // ������ ������ ��� ����� � Message c 9 �� 15 ����
#define PORT 7777 //   ����� �����



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
    char message[MESSAGE_LENGTH];                  // ��������� �� ������� 0 - ������� 1-8 - ����� 9-16 - ������ 17-1023 - ����


    vector<User> users;     // ������������������ ������������
    list<Message> logMsg;  // ������
};

