// PJ-04.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include "Chat.h"
#include <exception>
 #include "MyExceptions.h"
using namespace std;

int main()
{
    setlocale(LC_ALL, "");
    string hor_line = "\n----------------------------------\n";
    cout << "Добро пожаловать в чат!" << hor_line;
    char oper;
    Chat chat ;
    
    do
    {
        cout <<
            " Bведите команду:" << endl;
        cin >> oper;
        switch (oper)
        {
        case 'r':
        {
            chat.Registration();
            
        }
        break;
        case 'a':
        {
            chat.Autorisation();
        }
        break;
        case 'm':
        {
            try
            {
                
               if(! chat.SendMessage( ))
                            throw MessNotSent(); // если SendMessage вернула false, аварийное сообщение - не отправлено;
            }
            catch (exception& e)
            {
                cout << e.what();
            }
        }
        break;
        case 'l':
        {
            chat.ReadLog();
        }
        break;
        case 'h':
        {
            cout <<
                " Допустимые команды:"
                << "'r'  - регистрирaция нового пользователя (имя ALL - зарезервировано)" << endl
                << " 'a' - авторизация" << endl
                << " 'q'   выйти из программы  " << endl
                << "'h' - получить помошь " << endl
                << "'l' - прочесть архив ." << endl
                << "Авторизированный пользователь может" << endl
                << "'m'- написать сообщение получателю, " << endl
                << "если в имени получателя ввести ALL - сообщение всем участникам чата. " << endl
                
                ;
        }
        break;
        case 'q':
        {
            break;
        }

        default:
        {
            cout << "Неверный оператор!" << endl
                << "'h' - получить помошь " << endl;
            break;
        }
        }
        cout << hor_line << endl;
        chat.UsersList();
    } while (oper != 'q');

    return 0;




}
