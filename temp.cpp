#include <iostream>
#include <string.h>
#include <stdio.h>


bool validate(char * buffer);

using namespace std;

int main(){

 
  char buffer[1024] = "Hello world";
  return 0;

}

bool validate(char buffer []){
  
  string name, password;
  string username, userpassord;

  char * pch;
  pch = strtok(buffer, ":");
  strcpy(*pch, name);
  
  pch = strtok(null, " ");
  strcpy(*pch, password);
 
  cout << name << " " << password;

}
