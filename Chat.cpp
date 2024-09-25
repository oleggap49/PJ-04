#include "Chat.h"
#include <exception>
#include "MyExceptions.h"

bool Chat::Registration()

{
    string lgn;
    string pass;

    cout << " РЕГИСТРАЦИЯ" << endl;
    cout <<
        " Придумайте НИК:" << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    getline(cin, lgn);
    try
    {
        if (lgn == "ALL") throw ALLisreserved(); //имя ALL зарезнрвировано для групповой рассылки
         
        if (SearchNick(lgn))  throw UsernameExist();     // проверка, есть такой пользователь

        cout <<
            " Придумайте Пароль:" << endl;

        getline(cin, pass);

        User u1(lgn, pass, false);
        users.push_back(u1);
         
        cout << "Успешная регистрация " << u1.login << "!\n"
            << endl;
        return true;
    }
    catch (exception& e)
    {
        cout << e.what();
    }
    return false;
}

bool Chat::Autorisation() 
{
    string lgn;
    string pass;
    cout << " АВТОРИЗАЦИЯ" << endl;
    cout <<
        " Введите НИК:" << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    getline(cin, lgn);
    try
    {
        if (!SearchNick(lgn))
            throw UsernameNotExist(); //проверка, зарегистрирован ли такой пользователь

        cout <<
            " Введите пароль:" << endl;
        getline(cin, pass);
        vector<User>::iterator it = users.begin();
        for (; it != users.end(); it++)
            if (it->autorized == true) it->autorized = false;   // убираем предидущую авторизацию, если она была
        for (it = users.begin(); it != users.end(); it++)
        {
            if (it->login == lgn)
             if (it->password == pass)// проверка пароля
              {
               it->autorized=true ;  //признак , что пользователь авторизован
               cout << it->login << ", вы успешно авторизованы!" << endl;
               for (Message& msg : it->unreadMsg)   //сообщения авторизованному пользователю
               {
                   cout << msg.sender <<"->" << msg.recipient<<" : " << msg.text << endl; //выводим на экран
                    logMsg.push_back(msg);                    // добавляем в список журнала
                    it->unreadMsg.pop_front();               // убираем из очереди непрочтенных ( из начала)
               }
               return true;
              }
             else  throw WrongPassword();
        }
    }
    catch (exception& e)
    {
        cout << e.what();
    }
 return false;
}
// выводит на консоль количество и список загегистрированных пользователей
void Chat::UsersList()
{
    cout << "В чате - " << users.size() << " пользавателей." << endl;
    for (User& user : users) {
        cout << user.login <<  endl;
    }
    cout << endl;
}
// проверяет есть ли пользаватенль lgn в списке зарегистрированных
bool Chat::SearchNick(const string& lgn)
{
    
    vector<User>::iterator it = users.begin();
     
    for (; it != users.end(); it++)
    {

        if (it->login == lgn)
            return true;
    }
    return false;
  }
// отправка сообщения
bool Chat::SendMessage()
{
   
    try
    {
        vector<User>::iterator it = users.begin();

      for (; it != users.end(); it++)
      {

        if (it->autorized == true) // нашли авторизаванного пользователя
        {
             
               
            cout << "СООБЩЕНИЕ: " << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string Text;
            getline(cin, Text);                             // ввод текста сообщения
            cout << " Кому:" << endl;
            string reciepent;
            getline(cin, reciepent);
            
             
                
                vector<User>::iterator itR = users.begin();

                for (; itR != users.end(); itR++)
                {
                    if(reciepent =="ALL")
                    {
                        if (it->login == itR->login) continue; // самому себе не отправляем
                        Message msgAll(it->login, itR->login, Text);
                        itR->unreadMsg.push_back(msgAll);
                         
                    }
                    else
                        if (!SearchNick(reciepent))
                            throw UsernameNotExist(); //проверка, зарегистрирован ли такой пользователь
                    if (itR->login == reciepent) // нашли получателя
                    {
                        Message msg(it->login, reciepent, Text);
                        itR->unreadMsg.push_back(msg);                  // добавили в конец деки получателя
                        
                    }
                }
             return true;
        }
         
      } 
      throw NotAutorized();
    }
    catch (exception& e)
    {
        cout << e.what();
        return false;
    }
}
//выводит на консоль журнал (прочтенные сообщения)
void Chat::ReadLog()
{
    for (Message& msg : logMsg)
    {
        cout << msg.sender << "->" << msg.recipient << " : " << msg.text << endl;
     }
}

 

 