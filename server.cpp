#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

int main()
{

    int client, server;
    int portNum = 5000;
    bool isExit = false;
    int bufsize = 1024;
    char buffer[bufsize];

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

    // first check if it is valid or not
    if (server < 0) 
        cout << "=> Error on accepting..." << endl;
    
	/*Send Confirmation*/
	cout << "Accept Client" << endl;
	
    string msg = "Welcome!\nPlease Log In";

    send(server, msg.data(), msg.size(), 0);
	
	string userName, userPassword;
	//Recieve Username
	recv(server, buffer, bufsize, 0);
	

    cout << buffer;
	/*
	recv(server, buffer, bufsize, 0);
	userPassword = buffer;
	//Recieve UserPassword
    cout << userName << " " << userPassword << endl;
	//validate
    strcpy(buffer, "Valid");
    send(server, buffer, bufsize, 0);
    
    //Get credentials
    //
  */   
        cout << "\n\n=> Connection terminated with IP " << inet_ntoa(server_addr.sin_addr);
        close(server);
        cout << "\nGoodbye..." << endl;

    close(client);
    return 0;
}

/*
int validate(char [] buffer){
  
  string name, password;
  string username, userpassord;

  char * pch;
  pch = strtok(buffer, ":");
//  strcpy(pch, name);
  
  pch = strtok(buffer, ":");
 // strcpy(pch, password);
  

  return 0;

}*/
