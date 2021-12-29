#include <iostream>
#include <string>
#include <map>

int main(){
  std::map<std::string, std::string> phonebook;

  phonebook["John"] = "555-0000";
  phonebook["Paul"] = "555-1111";
  phonebook["Ring"] = "555-2222";
  phonebook["George"] = "555-3333";

  for( std::map<std::string,std::string>::iterator iter = phonebook.begin(); iter != phonebook.end(); iter++){
                  std::cout << iter->first << " " << iter->second << std::endl;
          }
  return 0;
}
