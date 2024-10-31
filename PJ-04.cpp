// PJ-04.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include "Chat.h"
#include <exception>
 #include "MyExceptions.h"
using namespace std;

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "");
    if (argc !=2)
    {
        cout << "Enter 'S' or 'C' argument to start Server or Client process " << endl;
        return 1;
    }
    
    if (*argv[1] == 'S')
    {
        Chat chat ;
     chat.StartTCPServer();
  if( chat.TCPServerDialogue())
        cout << "Server started "  << endl;
        return 0;
    }
    else if (*argv[1] == 'C')
    {
        User user;
        user.StartTCPClient();
        cout << "Client started "  << endl;
        user.TCPClientDialogue();
             
        return 0;
    }
    else
    {
        cout << "ERROR! Wrong command line argument!" << endl;
        return 1;
    }
    
    
    
     
}
