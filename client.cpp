#include <iostream>
#include <string>

void displayMenu();
int getOption();
int getPortNumber();
std::string getIpAddress();

int main(){


  int option, portNumber;
  std::string ipAddress;

  displayMenu();
  option= getOption();
  portNumber = getPortNumber();
  ipAddress= getIpAddress(); 
 
  std::cout << option << std::endl;
  std::cout << ipAddress << std::endl;
  std::cout << portNumber << std::endl;
  
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


