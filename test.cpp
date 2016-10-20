#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <string>

using namespace std;

bool validate(string, string);
string getUserList();

int main(){

/* 
  string name = "Alice";
  string password = "56789";

  if(validate(name, password))
    cout << "true";
  else
    cout << "false";
*/
  return 0;

  string list = getUserList();
  cout << list;

}

string getUserList(){
  
  ifstream file;
  file.open("userList");
  string list;

  while(file >> userName){
    
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
