#include <fstream>
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

bool validate(string, string);
string getUserList();
string getMessages(string);
void sendMessage(string, string);

int main()
{

    int client, server;
    int portNum = 8002;
    bool validUser = false;
    int bufsize = 1024;
    char buffer[bufsize];
	string userName, userPassword, msg;
    struct sockaddr_in server_addr;
    socklen_t size;

    client = socket(AF_INET, SOCK_STREAM, 0);

    if (client < 0) 
    {
        cout << "\nError establishing socket..." << endl;
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(portNum);

    if ((bind(client, (struct sockaddr*)&server_addr,sizeof(server_addr))) < 0) 
    {
        cout << "=> Error binding connection, the socket has already been established..." << endl;
        return -1;
    }

    size = sizeof(server_addr);
    cout << "=> Looking for clients..." << endl;

    listen(client, 1);
    server = accept(client,(struct sockaddr *)&server_addr,&size);

    if (server < 0) 
        cout << "=> Error on accepting..." << endl;
    
	/* Send Confirmation */
    msg = "Welcome!\nPlease Log In.";
    send(server, msg.data(), msg.length() + 1, 0);
	
	/* Wait for username */ 
	while(true){
	  
	  int n = recv(server, buffer, bufsize, 0);
	  userName += buffer;
	  
	  if(userName.find("\n") != std::string::npos)
	    break;

    }
    
	/* Wait for password */
	send(server, msg.data(), msg.length() + 1, 0);
   
	while(true){
	  
	  int n = recv(server, buffer, bufsize, 0);
	  userPassword += buffer;
	  
	  if(userPassword.find("\n") != std::string::npos)
	    break;

    }

	/* validate && remove '\n' */
    userName = userName.substr(0, userName.length()-1 );
	userPassword = userPassword.substr(0, userPassword.length()-1 );

    if(validate(userName, userPassword)){
	  msg = "Valid";
	  validUser = true;
	}
	else{
	  msg = "Invalid";
	  validUser = false;
	}
    
	/* Send if valid user or not */
    send(server, msg.data(), msg.length() + 1, 0);
    
/*****************************************************************************/
/*********** GET USER LIST WILL GO UNDER CASE 1:******************************/
/*****************************************************************************/

    /* Recieve option "1" */
    recv(server, buffer, bufsize, 0);
    
	/* Send list */
    msg = getUserList();
	send(server, msg.data(), msg.length() + 1, 0);
    
/*****************************************************************************/
/*********** SEND MESSAGES WILL GO UNDER CASE 2:******************************/
/*****************************************************************************/
	
    string sendUser, sendMessage; 

	/* Recieve option "2" */
	recv(server, buffer, bufsize, 0);
	msg = buffer;
	send(server, msg.data() , msg.length()+1, 0);

	/* Recieve user to send message to */
	recv(server, buffer, bufsize, 0);
	sendUser = buffer;
    send(server, msg.data(), msg.length()+1, 0);

	/* Recieve message to send */
    recv(server, buffer, bufsize, 0);
	sendMessage = buffer;
	send(server, msg.data(), msg.length()+1, 0);
    
	cout << msg << endl;
	cout << sendUser << endl;
	cout << sendMessage << endl;


/*****************************************************************************/
/*********** READ MESSAGES WILL GO UNDER CASE 3:******************************/
/*****************************************************************************/



    cout << "\n\n=> Connection terminated with IP " << inet_ntoa(server_addr.sin_addr);
    close(server);
    cout << "\nGoodbye..." << endl;

    close(client);
    return 0;
}


bool validate(string name, string password){
  
  string userName, userPassword;
    
  ifstream file;
  file.open("userList");
  
  while(file >> userName){
    
    file >> userPassword;

    if(userName.compare(name) == 0){
    
	  if(userPassword.compare(password) == 0)
        return true;
	  else
	    return false;
  
    }
  
  }

  return false;

}

string getUserList(){
  
  ifstream file;
  file.open("userList");
  string message, list, userPassword, userName;
  int count;

  count = 0;

  while(file >> userName){
    file >> userPassword;    
	list += userName + '\n';
	count++;
  }

  message = "There are " + to_string(count) + " users.\n";
  message += list;

  return message;

}


void sendMessage(string name, string message){
  
  ofstream file;
  file.open(name, ios::app);
  
  message += '\n';

  file << message;

  file.close();
 
}

string readMessages(string name){
  
  ifstream file;
  file.open(name);

  string line, message;

  while( getline(file, line) ){
    
	line += '\n';
	message += line;

  }
  
  /* Remove last '\n' character */
  message = message.substr(0, message.length()-1);

  file.close();
  
  /* clear all data */
  ofstream ofs(name);
  ofs.close();

  return message;

}
