#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>

using namespace std;

void displayMenu();
void initializeChat(string);
void chat(string);

int main()
{

  int client, portNum;
  bool connected;
  int bufsize = 1024;
  char buffer[bufsize];
  char * ipPtr = (char*)malloc(100);
  string ipaddress, user, msg, option;
  
  while(true){
    connected = false;
    displayMenu();
    cout << "Your option<enter a number>: ";
    getline(cin, option);
    
    switch( atoi(option.c_str()) ){

      case 0:{
        
	/* Connect to Server */
        if(!connected){	
        
	  cout << "Please enter the IP Address: ";
          getline(cin, ipaddress);
          cout << "Please enter the port number: ";
          cin >> portNum;
          strcpy(ipPtr, ipaddress.c_str());
        
	  /*connect to server*/
          struct sockaddr_in server_addr; 
          client = socket(AF_INET, SOCK_STREAM, 0);
        	
          if (client < 0)
            exit(1);
        
          server_addr.sin_family = AF_INET;
          server_addr.sin_port = htons(portNum);
          server_addr.sin_addr.s_addr = inet_addr(ipPtr);

          /*connect socket*/
          if((connect(client,(struct sockaddr *)&server_addr, sizeof(server_addr)) == 0))
            cout << "Connecting..." << endl;
        
          /* Wait for connection confirmation */	
          recv(client, buffer, bufsize, 0); 
          cout << buffer << endl;
          cin.ignore();
        }
	
	/* Get Login */
	while(true){
          
	  /* Send Username */
	  cout << "Username: ";
          getline(cin,msg);
          user = msg;
	  send(client, msg.data(), msg.length() + 1, 0);
	  recv(client, buffer, bufsize, 0);
    
	  /* Send Password */
          cout << "Password: ";
          getline(cin,msg);
	  send(client, msg.data(), msg.length() + 1, 0);
    
          /* Wait for authentication */
	  recv(client, buffer, bufsize, 0);
	  msg = buffer;

          /*get authentication*/
	  if(msg.compare("Valid") == 0)
	    break;
	  else
	    cout << "login failure" << endl;
        
	} 
        
	connected = true;
	cout << "login success" << endl;
	break;
      }   
/*****************************************************************************/
/*********** GET USER LIST WILL GO UNDER CASE 1:******************************/
/*****************************************************************************/
      case 1:{

	/* send option '1'*/
	send(client, option.data(), option.length() + 1, 0);
	
	/* recieve list */
	recv(client, buffer, bufsize, 0);
	msg = buffer;
   
	/*display list*/
        cout << msg << endl;
        

        break;
      }  
/*****************************************************************************/
/*********** SEND MESSAGES WILL GO UNDER CASE 2:******************************/
/*****************************************************************************/
      case 2:{
        
        /* Send Option 2 */ 
	send(client, option.data(), option.length()+1, 0);
        recv(client, buffer, bufsize, 0);

	/* Send User Name */
	cout << "Please enter the user name: ";
        getline(cin, msg);
	send(client, msg.data(), msg.length()+1, 0);
	recv(client, buffer, bufsize, 0);
    
	/* Send message */
        cout << "Please enter the message: ";
	getline(cin, msg);
	send(client, msg.data(), msg.length()+1, 0);
        recv(client, buffer, bufsize, 0);
        
        break;

      }  
/*****************************************************************************/
/*********** READ MESSAGES WILL GO UNDER CASE 3:******************************/
/*****************************************************************************/
      case 3:{
	
        /* Send option 3 */
	send(client, option.data(), option.length()+1, 0);
        
        /* Recieve messages */
        recv(client, buffer, bufsize, 0); 	
        cout << buffer << endl;

        break;

      }
/*****************************************************************************/
/*********** CASE 4: Initiate a chat *****************************************/
/*****************************************************************************/
      case 4:{
        connected = false; 
	send(client, option.data(), option.length()+1, 0);
        shutdown(client, 2);
	initializeChat(user); 
        break;
      }
/*****************************************************************************/
/*********** READ MESSAGES WILL GO UNDER CASE 3:******************************/
/*****************************************************************************/
      case 5:{
        connected = false;
        send(client, option.data(), option.length()+1, 0);
	shutdown(client, 2);
	chat(user);
        break;	
      }
      case 6:{
        close(client);
	return 0;
      }

    }//end switch
  
  }//end while loop

  shutdown(client, 2);
  return 0;
}

void displayMenu(){

  std::cout << "0. Connect to the server" << std::endl; 
  std::cout << "1. Get the user list" << std::endl;
  std::cout << "2. Send a message" << std::endl;
  std::cout << "3. Get my messages" << std::endl;
  std::cout << "4. Initiniate a chat with my friend" << std::endl;
  std::cout << "5. Chat with my friend" << std::endl;

}

int getOption(){
  
  int option;

  std::cout << "Your option<eenter a number>: ";
  std::cin >> option;

  return option;

}

int getPortNumber(){

  int portNumber;

  std::cout << "Please enter the port number: ";
  std::cin >> portNumber;

  return portNumber;
}

std::string getIpAddress(){

  std::string ipAddress;

  std::cout << "Please enter the ip address: " ;
  std::cin >> ipAddress;

  return ipAddress;

}

void initializeChat(string user){

  int portNum, client, server;
  int bufsize = 1024;
  char buffer[bufsize];
  string msg, input;
  struct sockaddr_in server_addr;
  socklen_t size;
  
  /* Get port info */
  cout << "Please enter the port number you want to listen on: ";
  getline(cin, input);
  portNum = atoi(input.c_str());

  if((client = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    exit(1);
   
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htons(INADDR_ANY);
  server_addr.sin_port = htons(portNum);
  size = sizeof(server_addr);

  if ((bind(client, (struct sockaddr*)&server_addr,sizeof(server_addr))) < 0) 
  {
    cout << "=> Error binding connection, the socket has already been established..." << endl;
    exit(1);
  }

  /* Listen */
  cout << "I am listening on 127.0.0.1:" << portNum << endl;
  listen(client, 1);
  server = accept(client,(struct sockaddr *)&server_addr,&size);
    
  /* Send Confirmation */
  msg = "Connected!";
  send(server, msg.data(), msg.length() + 1, 0);
  cout << "Connected. " << endl;

  string outmsg;
  user += ": ";
  char * check = NULL;
  while(true){
    
    /* recieve  message */
    recv(server, buffer, bufsize, 0);
    cout << buffer << endl;

    /* Check for Bye */
    check = strstr(buffer, "Bye");
    if(check)
      break;

    /* send message */
    outmsg = user; 
    cout << user;
    getline(cin, msg);
    outmsg += msg;
    send(server, outmsg.data(), outmsg.length()+1, 0);
    
    /* Check for bye */
    check = strstr(outmsg.c_str(), "Bye");
    if(check)
      break;

  }
  
  shutdown(server, 2);
  shutdown(client, 2);
  close(server);
  close(client);
}

void chat(string user){

  int client, portNum;
  int bufsize = 1024;
  char buffer[bufsize];
  char * ipPtr = (char*)malloc(100);
  char * check = NULL;
  string ipaddress, msg, outmsg;
  
  /* Get info */
  cout << "Please enter your friend's IP Address: ";
  getline(cin, ipaddress); 
  cout << "Please enter your friend's port number: ";
  cin >> portNum;
  strcpy(ipPtr, ipaddress.c_str());
  
  cin.ignore();

  /*connect to server*/
  struct sockaddr_in server_addr; 
  client = socket(AF_INET, SOCK_STREAM, 0);
        	
  if (client < 0)
    exit(1);
        
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(portNum);
  server_addr.sin_addr.s_addr = inet_addr(ipPtr);
  /*connect socket*/
  
  if((connect(client,(struct sockaddr *)&server_addr, sizeof(server_addr)) == 0))
    cout << "Connecting..." << endl;
        
  /* Wait for connection confirmation */	
  recv(client, buffer, bufsize, 0); 
  cout << buffer << endl;
  
  /* Send first message */
  cout << "<Type \"Bye\" to stop the conversation>" << endl; 
  user += ": ";
  
  while(true){
    
    /* send message */
    outmsg = user;
    cout << user;
    getline(cin, msg);
    outmsg += msg;   
    send(client, outmsg.data(), outmsg.length()+1, 0);
    
    /*check for Bye*/
    check = strstr(outmsg.c_str(), "Bye");
    if(check)
      break;

    /*recieve message */
    recv(client, buffer, bufsize, 0);
    cout << buffer << endl;

    /*check for Bye*/
    check = strstr(buffer, "Bye");
    if(check)
      break;
  
  }

  shutdown(client, 2);
  
}
