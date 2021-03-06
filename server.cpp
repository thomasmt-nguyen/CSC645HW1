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
string readMessages(string);
void sendMessages(string, string);

int main()
{
  
  int client;
  int portNum = 8016;
  bool validUser = false;
  bool online;
  int bufsize = 1024;
  char buffer[bufsize];
  string userName, userPassword, msg;
  struct sockaddr_in server_addr;
  socklen_t size; 

  if((client = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    exit(1);
    
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htons(INADDR_ANY);
  server_addr.sin_port = htons(portNum);
  size = sizeof(server_addr);

  if ((bind(client, (struct sockaddr*)&server_addr,sizeof(server_addr))) < 0) 
  {
    cout << "=> Error binding connection, the socket has already been established..." << endl;
    return -1;
  }

  while(true){
    
    int server;
    online = false;

    cout << "=> Looking for clients..." << endl;

    listen(client, 1);
    server = accept(client,(struct sockaddr *)&server_addr,&size);

    if (server > 0) 
      cout << "Client has connected." << endl;
    
    /* Send Confirmation */
    msg = "Welcome!\nPlease Log In.";
    send(server, msg.data(), msg.length() + 1, 0);
    
    while(true){
      
      /* Wait for username */
      recv(server, buffer, bufsize, 0);
      userName = buffer;
 
      /* Wait for password */
      send(server, msg.data(), msg.length() + 1, 0);
      recv(server, buffer, bufsize, 0);
      userPassword = buffer;
	
      /* validate */
      if(validate(userName, userPassword)){
        cout << "User has logged in" << endl;
        msg = "Valid";
        online = true;
        send(server, msg.data(), msg.length() + 1, 0);
	break;
      }
      else{
        cout << "user login failed." << endl;
        msg = "Invalid";
        send(server, msg.data(), msg.length() + 1, 0);
      }

    }
    
    /* Send if valid user or not */


/*****************************************************************************/
/*********** LOG ON WILL GO UNDER CASE 0:************************************/
/*****************************************************************************/
	
    while(online){
      
      /* get option */
      recv(server, buffer, bufsize, 0);	  
      switch( atoi(buffer) ){
        
/*****************************************************************************/
/*********** CASE 0: LOGGING ON **********************************************/
/*****************************************************************************/
	case 0:{
           
          /* Wait for username */ 
          recv(server, buffer, bufsize, 0);
          userName = buffer;
 
          /* Wait for password */
          send(server, msg.data(), msg.length() + 1, 0);
          recv(server, buffer, bufsize, 0);
          userPassword = buffer;
	
          /* validate */
          if(validate(userName, userPassword)){
            cout << "User has logged in" << endl;
            msg = "Valid";
            validUser = true;
            online = true;
          }
          else{
            cout << "user login failed." << endl;
            msg = "Invalid";
            validUser = false;
            exit(0);
          }
    
          /* Send if valid user or not */
          send(server, msg.data(), msg.length() + 1, 0);
	
	break;
		
	}  
/*****************************************************************************/
/*********** GET USER LIST WILL GO UNDER CASE 1:******************************/
/*****************************************************************************/
        case 1:{

	  /* Send list */
          msg = getUserList();
	  send(server, msg.data(), msg.length() + 1, 0);
          cout << "Userlist has been sent." << endl; 
          break;
		
	}
/*****************************************************************************/
/*********** SEND MESSAGES WILL GO UNDER CASE 2:******************************/
/*****************************************************************************/
	case 2:{
          
          string sendUser, sendMessage; 
          send(server, msg.data(), msg.length()+1, 0);

	  /* Recieve user to send message to */
	  recv(server, buffer, bufsize, 0);
	  sendUser = buffer;
          send(server, msg.data(), msg.length()+1, 0);

	  /* Recieve message to send */
          recv(server, buffer, bufsize, 0);
          sendMessage = buffer;
          send(server, msg.data(), msg.length()+1, 0);
    
	  /* Write message */
	  sendMessages(sendUser, sendMessage);
          
          /* Log onto consol */
          cout << userName << " has sent a message to " << sendUser << endl;
		  
          break;

        }
/*****************************************************************************/
/*********** READ MESSAGES WILL GO UNDER CASE 3:******************************/
/*****************************************************************************/
        case 3:{ 
	      
          string readMessage;
          readMessage = readMessages(userName);
	
	  /* Send users messages */
	  send(server, readMessage.data(), readMessage.length()+1, 0); 
          cout << userName << " has received their messages." << endl;
		  
          break;
        
	}
/*****************************************************************************/
/*********** READ MESSAGES WILL GO UNDER CASE 3:******************************/
/*****************************************************************************/
	case 4:
	case 5:{
	      
          cout << "Client has disconnected." << endl;
	  online = false;
        
          //shutdown(server, 2);
	  shutdown(client, 2);
          break;
 
        }	

/*****************************************************************************/
/*********** READ MESSAGES WILL GO UNDER CASE 3:******************************/
/*****************************************************************************/
	case 6:{
          cout.flush(); 
          cout << "Shutting down server." << endl;
          shutdown(server, 2);
          shutdown(client, 2);
          return 1;
   
	}

      }//End of switch
    
    }//End of while loop
  
  }//End of while loop

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


void sendMessages(string name, string message){
  
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
