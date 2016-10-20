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

int main()
{

  int client, portNum;
  bool isExit = false;
  int bufsize = 1024;
  char buffer[bufsize];
  char * ipPtr = (char*)malloc(100);
  string ipaddress, msg, option;

  while(true){

    displayMenu();
    cout << "Your option<enter a number>: ";
    getline(cin, option);
    
    switch( atoi(option.c_str()) ){

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
        getline(cin,msg);
	    msg += '\n';	
 	    send(client, msg.data(), msg.length() + 1, 0);
   
	    recv(client, buffer, bufsize, 0);
        //cout << msg << endl;
    
	    /* Send Password */
	    cout << "Password: ";
        getline(cin,msg);
        msg += '\n';
	    send(client, msg.data(), msg.length() + 1, 0);
    
         /* Wait for authentication */
	     recv(client, buffer, bufsize, 0);
         msg = buffer;

	     /*get authentication*/
	     if(msg.compare("Valid") == 0)
		   cout << "login success" << endl;
		 else
		   cout << "login failure" << endl;
       
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
/*********** READ MESSAGES WILL GO UNDER CASE 3:******************************/
/*****************************************************************************/
      case 4:{
	    
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


