#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <string>

using namespace std;

bool validate(string, string);
string getUserList();
string readMessages(string);
void sendMessage(string, string);

int main(){

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

  sendMessage("Alice", "this is a line bruh");
  
  string message = readMessages("Alice");
  cout << message << endl;

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
