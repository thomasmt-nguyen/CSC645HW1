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
    
	/* Random */
    recv(server, buffer, bufsize, 0);
    
	/* Send list */
    msg = getUserList();

	send(server, msg.data(), msg.length() + 1, 0);

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
  string list, userPassword, userName;

  while(file >> userName){
	cout << userName;    
    file >> userPassword;    
	list += userName + '\n';    
  }

  return list;

}
