#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>
 
using namespace std;
class Chat
{
public:
    Chat()  
    {
        users.emplace_back("admin", "admin", true);
    }

    ~Chat() {}

    bool Registration();
    bool Autorisation();
    void UsersList();
    bool SearchNick(const string& lgn);
    bool SendMessage();
    void ReadLog();
     
 
private:
    struct Message
    {
        string sender;
        string recipient;
        string text;
        Message(const string& snd, const string& rec, const string& txt) :
            sender(snd), recipient(rec), text(txt)  {};
    };
    struct User
    {
        string login;
        string password;
        bool admin;
        bool autorized;
        deque<Message> unreadMsg;           // контейнер непрочтенных сообщений пользователя. Новые добавляем в конецБ прочтенные удаляем из начала и перемещаем в журнал logMsg
        User(const string& lgn, const string& pass, const bool adm) :
            login(lgn), password(pass), admin(adm), autorized(false) {};
    };
    
    vector<User> users;     // зарегистрированные пользователи
    list<Message> logMsg;  // журнал
};