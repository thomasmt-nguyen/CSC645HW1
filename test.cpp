#include <fstream>
#include <iostream>
#include <string.h>
#include <stdio.h>
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
void sendMessage(string, string);

int main(){

  int client, portNum;
  int bufsize = 1024;
  char buffer[bufsize];
  char * ipPtr = (char*)malloc(100);
  char * check = NULL;
  string ipaddress, user, msg, outmsg;
  
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
  user = "Bob: ";
  
  while(true){
    
    /* send message */
    user = "Bob: ";
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


















/* 
  string name = "Alice";
  string password = "56789";

  if(validate(name, password))
    cout << "true";
  else
    cout << "false";
*/
  
/*
  string list = getUserList();
  cout << list;
  */

/*
  sendMessage("Alice", "this is a line bruh");
  
  string message = readMessages("Alice");
  cout << message << endl;
*/
  return 0;
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

/*test file for validate*/
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
