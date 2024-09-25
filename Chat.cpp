#include "Chat.h"
#include <exception>
#include "MyExceptions.h"

bool Chat::Registration()

{
    string lgn;
    string pass;

    cout << " �����������" << endl;
    cout <<
        " ���������� ���:" << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    getline(cin, lgn);
    try
    {
        if (lgn == "ALL") throw ALLisreserved(); //��� ALL ��������������� ��� ��������� ��������
         
        if (SearchNick(lgn))  throw UsernameExist();     // ��������, ���� ����� ������������

        cout <<
            " ���������� ������:" << endl;

        getline(cin, pass);

        User u1(lgn, pass, false);
        users.push_back(u1);
         
        cout << "�������� ����������� " << u1.login << "!\n"
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
    cout << " �����������" << endl;
    cout <<
        " ������� ���:" << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    getline(cin, lgn);
    try
    {
        if (!SearchNick(lgn))
            throw UsernameNotExist(); //��������, ��������������� �� ����� ������������

        cout <<
            " ������� ������:" << endl;
        getline(cin, pass);
        vector<User>::iterator it = users.begin();
        for (; it != users.end(); it++)
            if (it->autorized == true) it->autorized = false;   // ������� ���������� �����������, ���� ��� ����
        for (it = users.begin(); it != users.end(); it++)
        {
            if (it->login == lgn)
             if (it->password == pass)// �������� ������
              {
               it->autorized=true ;  //������� , ��� ������������ �����������
               cout << it->login << ", �� ������� ������������!" << endl;
               for (Message& msg : it->unreadMsg)   //��������� ��������������� ������������
               {
                   cout << msg.sender <<"->" << msg.recipient<<" : " << msg.text << endl; //������� �� �����
                    logMsg.push_back(msg);                    // ��������� � ������ �������
                    it->unreadMsg.pop_front();               // ������� �� ������� ������������ ( �� ������)
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
// ������� �� ������� ���������� � ������ ������������������ �������������
void Chat::UsersList()
{
    cout << "� ���� - " << users.size() << " �������������." << endl;
    for (User& user : users) {
        cout << user.login <<  endl;
    }
    cout << endl;
}
// ��������� ���� �� ������������� lgn � ������ ������������������
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
// �������� ���������
bool Chat::SendMessage()
{
   
    try
    {
        vector<User>::iterator it = users.begin();

      for (; it != users.end(); it++)
      {

        if (it->autorized == true) // ����� ��������������� ������������
        {
             
               
            cout << "���������: " << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string Text;
            getline(cin, Text);                             // ���� ������ ���������
            cout << " ����:" << endl;
            string reciepent;
            getline(cin, reciepent);
            
             
                
                vector<User>::iterator itR = users.begin();

                for (; itR != users.end(); itR++)
                {
                    if(reciepent =="ALL")
                    {
                        if (it->login == itR->login) continue; // ������ ���� �� ����������
                        Message msgAll(it->login, itR->login, Text);
                        itR->unreadMsg.push_back(msgAll);
                         
                    }
                    else
                        if (!SearchNick(reciepent))
                            throw UsernameNotExist(); //��������, ��������������� �� ����� ������������
                    if (itR->login == reciepent) // ����� ����������
                    {
                        Message msg(it->login, reciepent, Text);
                        itR->unreadMsg.push_back(msg);                  // �������� � ����� ���� ����������
                        
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
//������� �� ������� ������ (���������� ���������)
void Chat::ReadLog()
{
    for (Message& msg : logMsg)
    {
        cout << msg.sender << "->" << msg.recipient << " : " << msg.text << endl;
     }
}

 

 