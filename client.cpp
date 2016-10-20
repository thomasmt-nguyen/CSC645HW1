#include <iostream>
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

int main()
{

  int client, option, portNum;
  bool isExit = false;
  int msgsize = 1024;
  char msg[msgsize];
  char * ipPtr = (char*)malloc(100);
  string ipaddress, name, password;


  
  while(true){

    displayMenu();
    cout << "Your option<enter a number>: ";
    cin >> option;
    
    switch(option){

      case 0:{
    
        cout << "Please enter the IP Address: ";
        cin >> ipaddress; 
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

	/*connect socket*/
        if((connect(client,(struct sockaddr *)&server_addr, sizeof(server_addr)) == 0))
          cout << "Connecting..." << endl;
        
	/*recieve confirmation*/	
    /*Will receive "Welcome!\n Please Log in*/
	recv(client, msg, msgsize, 0); 
	cout << msg << endl;
    cin.ignore();

	cout << "Username: ";
    getline(cin,name);
	name += '\n';	
 	send(client, name.data(), name.length() + 1, 0);
    
	
	recv(client, msg, msgsize, 0);
    //cout << msg << endl;
    
	cout << "Password: ";
    getline(cin,password);
    password += '\n';
	send(client, password.data(), password.length() + 1, 0);
	/*
	cout << "Password: ";
	cin >> password;
	strcpy(buffer, password.c_str());

	send(client, buffer, bufsize, 0);

	authentication = name + ":" + password;
	if(strcmp(buffer, "Valid") != 0){
	  cout << "Invalid Login" << endl;
	  break;
	}


*/


        // Once it reaches here, the client can send a message first.
        cout << "\n=> Connection terminated.\nGoodbye...\n";
        close(client);
	break; 
      }
      case 1:{
      //get list of users 
            
        close(client);
        exit(0);
	break;
      }
      case 5:{
	close(client);
        break;
      }

    }//end switch
  
  }//end while loop

  close(client);
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


