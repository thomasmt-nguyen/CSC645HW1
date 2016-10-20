#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <string>

using namespace std;

bool validate(string, string);

int main(){

 
  string name = "Alice";
  string password = "56789";

  if(validate(name, password))
    cout << "true";
  else
    cout << "false";

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
