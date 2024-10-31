#include "Chat.h"
#include <exception>
#include "MyExceptions.h"

void Chat::StartTCPServer()
{
     
    socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_file_descriptor == -1) {
        cout << "Socket creation failed.!" << endl;
        exit(1);
    }
    
    serveraddress.sin_addr.s_addr = htonl(INADDR_ANY);
     
    serveraddress.sin_port = htons(PORT);
     
    serveraddress.sin_family = AF_INET;
    
    bind_status = bind(socket_file_descriptor, (struct sockaddr*)&serveraddress,
        sizeof(serveraddress));
    if (bind_status == -1) {
        cout << "Socket binding failed.!" << endl;
        exit(1);
    }
     
    connection_status = listen(socket_file_descriptor, 5);
    if (connection_status == -1) {
        cout << "Socket is unable to listen for new connections.!" << endl;
        exit(1);
    }
    else {
        cout << "Server is listening for new connection: " << endl;
    }
    length = sizeof(client);
    connection = accept(socket_file_descriptor, (struct sockaddr*)&client, &length);
    if (connection == -1) {
        cout << "Server is unable to accept the data from client.!" << endl;
        exit(1);
    }
}

 

int Chat::TCPServerDialogue()
{
    char oper;
string res = "\n";
     do
    {
            
              // send to user
              bzero(message, MESSAGE_LENGTH);
              strcat(message, res.c_str());
//cout << message <<endl;

              strcat(message, "Enter command: ");
 
              ssize_t bytes = write(connection, message, sizeof(message));
              // get from user
         bzero(message, MESSAGE_LENGTH);
         read(connection, message, sizeof(message));
       //  cout << "Data received from client: " << message << endl;

        if (strncmp("end", message, 3) == 0) 
        {
            cout << "Client Exited." << endl;
            cout << "Server is Exiting..!" << endl;
            break;
        }
     oper = message[0];
       // cin >> oper;
        switch (oper)
        {
        case 'r':
        {
             Registration();
               
               res ="Successfull registation \n" ;
              
            
        }
        break;
        case 'a':
        {
             Autorisation();
             res ="Successfull  autorization \n" ;
        }
        break;
        case 'm':
        {
            try
            {
                
               if(!  SendMessage( ))
                            throw MessNotSent(); 
            }
            catch (exception& e)
            {
                cout << e.what();
            }
             res ="Message sent \n" ;
        }
        break;
        case 'l':
        {
             ReadLog();
             res ="Log read\n" ;
        }
        break;
        case 'h':
        {
            cout <<
                " Valid commands:"
                << "'r'  - registration(name ALL - reserved)" << endl
                << " 'a' - autorization" << endl
                << " 'end'   exit  " << endl
                << "'h' - help " << endl
                << "'l' - read log ." << endl
                
                << "'m'- send a message, " << endl
                                ;
        }
        break;
        

        default:
        {
            cout << "Wrong command!" << endl
                << "'h' - get help " << endl;
            break;
        }
        }
      //  cout << hor_line << endl;
         UsersList();
    } while (1);

    close(socket_file_descriptor);
    return 0;
}


bool Chat::Registration()

{
    string lgn;
    string pass;
               // send to user
              bzero(message, MESSAGE_LENGTH);
              strcat(message, " Registration \nEnter login: ");
              ssize_t bytes = write(connection, message, sizeof(message));
              bytes = 0;
         // get from user
         bzero(message, MESSAGE_LENGTH);
         read(connection, message, sizeof(message));
        // cout << "Data received from client: " << message << endl;

    lgn=message;
    try
    {
        if (lgn == "ALL") throw ALLisreserved();  
         
        if (SearchNick(lgn))  throw UsernameExist();      

              // send to user
              bzero(message, MESSAGE_LENGTH);
              strcat(message, " Enter Password: ");
               bytes = write(connection, message, sizeof(message));
               bytes = 0;
         // get from user
         bzero(message, MESSAGE_LENGTH);
         read(connection, message, sizeof(message));
        // cout << "Data received from client: " << message << endl;
        pass = message;

        User u1(lgn, pass, false);
        users.push_back(u1);
         
        cout << "Registation -  " << u1.getLogin()  
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
    
 // send to user
              bzero(message, MESSAGE_LENGTH);
              strcat(message, " Autorization \nEnter login: ");
              ssize_t bytes = write(connection, message, sizeof(message));
              bytes = 0;
         // get from user
         bzero(message, MESSAGE_LENGTH);
         read(connection, message, sizeof(message));
        // cout << "Data received from client: " << message << endl;

    lgn=message;
 
    try
    {
        if (!SearchNick(lgn))
            throw UsernameNotExist();  
 
              bzero(message, MESSAGE_LENGTH);
              strcat(message, "  Enter password: ");
              ssize_t bytes = write(connection, message, sizeof(message));
              bytes = 0;
         // get from user
         bzero(message, MESSAGE_LENGTH);
         read(connection, message, sizeof(message));
       //  cout << "Data received from client: " << message << endl;         
 pass=message;
        vector<User>::iterator it = users.begin();
        for (; it != users.end(); it++)
            if (it->getAutorized() == true) it->setAutorized (false);     
        for (it = users.begin(); it != users.end(); it++)
        {
            if (it->getLogin() == lgn)
             if (it->getPassword() == pass) 
              {
               it->setAutorized(true) ;   
              cout << it->getLogin() << " autorized." << endl;
               
               for (Message& msg : it->unreadMsg)   
               {
                   cout << msg.sender <<"->" << msg.recipient<<" : " << msg.text << endl; 
                 
              bzero(message, MESSAGE_LENGTH);
              strcat(message, msg.sender.c_str()  );
              strcat(message, "->"   );
              strcat(message, msg.recipient.c_str()  );
              strcat(message, " : "   ); 
              strcat(message, msg.text.c_str()  );
              strcat(message, "\nEnter "" read""" );
              ssize_t bytes = write(connection, message, sizeof(message));
              bytes = 0;
              bzero(message, MESSAGE_LENGTH);
              read(connection, message, sizeof(message));
                    logMsg.push_back(msg);                     
                    it->unreadMsg.pop_front();               
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
 
void Chat::UsersList()
{
    cout << "There are    " << users.size() << " users in the chat now." << endl;
    for (User& user : users) {
        cout << user.getLogin() <<  endl;
    }
    cout << endl;
}
 
bool Chat::SearchNick(const string& lgn)
{
    
    vector<User>::iterator it = users.begin();
     
    for (; it != users.end(); it++)
    {

        if (it->getLogin() == lgn)
            return true;
    }
    return false;
  }
 
bool Chat::SendMessage()
{
   
    try
    {
        vector<User>::iterator it = users.begin();

      for (; it != users.end(); it++)
      {

        if (it->getAutorized() == true)  
        {
            string Text; 
            string reciepent;  

        
             bzero(message, MESSAGE_LENGTH);
              strcat(message, " Message:  ");
              ssize_t bytes = write(connection, message, sizeof(message));
              bytes = 0;
         // get from user
         bzero(message, MESSAGE_LENGTH);
         read(connection, message, sizeof(message));
       //  cout << "Data received from client: " << message << endl;

    Text=message;
             
           bzero(message, MESSAGE_LENGTH);
              strcat(message, " Reciepent:  ");
               bytes = write(connection, message, sizeof(message));
              bytes = 0;
         // get from user
         bzero(message, MESSAGE_LENGTH);
         read(connection, message, sizeof(message));
         //cout << "Data received from client: " << message << endl;

    reciepent=message;     
                vector<User>::iterator itR = users.begin();

                for (; itR != users.end(); itR++)
                {
                    if(reciepent =="ALL")
                    {
                        if (it->getLogin() == itR->getLogin()) continue;  
                        Message msgAll(it->getLogin(), itR->getLogin(), Text);
                        itR->unreadMsg.push_back(msgAll);
                         
                    }
                    else
                        if (!SearchNick(reciepent))
                            throw UsernameNotExist();   
                    if (itR->getLogin() == reciepent)  
                    {
                        Message msg(it->getLogin(), reciepent, Text);
                        itR->unreadMsg.push_back(msg);                    
                        
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

void Chat::ReadLog()
{
    for (Message& msg : logMsg)
    {
        cout << msg.sender << "->" << msg.recipient << " : " << msg.text << endl;
              bzero(message, MESSAGE_LENGTH);
              strcat(message, msg.sender.c_str()  );
              strcat(message, "->"   );
              strcat(message, msg.recipient.c_str()  );
              strcat(message, " : "   ); 
              strcat(message, msg.text.c_str()  );
              strcat(message, "\nEnter "" read""" );
              ssize_t bytes = write(connection, message, sizeof(message));
              bytes = 0;
              bzero(message, MESSAGE_LENGTH);
              read(connection, message, sizeof(message));
                          
     }
}

 

 
