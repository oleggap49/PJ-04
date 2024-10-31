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

#define MESSAGE_LENGTH 1024 // ������������ ������ ������ ��� ������
#define LOGIN_LENGTH 8      // ������ ������ ��� ����� � Message c 1 �� 8 ����
#define PASS_LENGTH  8      // ������ ������ ��� ����� � Message c 9 �� 15 ����
#define PORT 7777 //   ����� �����

using namespace std;
struct Message
{
    string sender;
    string recipient;
    string text;
    Message(const string& snd, const string& rec, const string& txt) :
        sender(snd), recipient(rec), text(txt) {};
};
class User
{
    string login;
    string password;
    bool admin;
    bool autorized;

    struct sockaddr_in serveraddress, client;
    socklen_t length;
    int socket_file_descriptor, connection, bind_status, connection_status;
    char message[MESSAGE_LENGTH];                  // ��������� �� ������� 0 - ������� 1-8 - ����� 9-16 - ������ 17-1023 - ����

public:
    User() = default;
    User(const string& lgn, const string& pass, const bool adm) :
        login(lgn), password(pass), admin(adm), autorized(false) {};
    string getLogin() { return (login); }
    string getPassword() { return (password); }
    bool getAdmin() { return admin; }
    bool getAutorized() { return autorized; }
    void setAutorized(bool aut) { autorized = aut; }
   
    void StartTCPClient();
    int TCPClientDialogue();
         

    deque<Message> unreadMsg; // ��������� ������������ ��������� ������������. ����� ��������� � �����, ���������� ������� �� ������ � ���������� � ������ logMsg
};
