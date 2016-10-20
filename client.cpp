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
  int bufsize = 1024;
  char buffer[bufsize];
  char * ipPtr = (char*)malloc(100);
  string ipaddress, msg, name, password;

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
        
	/* Wait for connection confirmation */	
	recv(client, buffer, bufsize, 0); 
	cout << buffer << endl;
    cin.ignore();
    
	/* Send Username */
	cout << "Username: ";
    getline(cin,name);
	name += '\n';	
 	send(client, name.data(), name.length() + 1, 0);
   
	recv(client, buffer, bufsize, 0);
    //cout << msg << endl;
    
	/* Send Password */
	cout << "Password: ";
    getline(cin,password);
    password += '\n';
	send(client, password.data(), password.length() + 1, 0);
    
    /* Wait for authentication */
	recv(client, buffer, bufsize, 0);
    msg = buffer;

	/*get authentication*/
	cout << msg << endl;
    

    
/*****************************************************************************/
/*********** GET USER LIST WILL GO UNDER CASE 1:******************************/
/*****************************************************************************/

	/* send option '1'*/
	msg = "1";
	send(client, msg.data(), msg.length() + 1, 0);
	
	/* recieve list */
	recv(client, buffer, bufsize, 0);
	msg = buffer;
   
    
	/*display list*/
	cout << msg << endl;
    
/*****************************************************************************/
/*********** SEND MESSAGES WILL GO UNDER CASE 2:******************************/
/*****************************************************************************/

    /* Send Option 1 */
	msg = "2";
	send(client, msg.data(), msg.length()+1, 0);
    
	/* Recieve confirm option recieved */
	msg = "Alice";
	send(client, msg.data(), msg.length()+1, 0);
	recv(client, buffer, bufsize, 0);
    
	msg = "This is a message";
	send(client, msg.data(), msg.length()+1, 0);
	recv(client, buffer, bufsize, 0);

/*****************************************************************************/
/*********** READ MESSAGES WILL GO UNDER CASE 3:******************************/
/*****************************************************************************/
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


