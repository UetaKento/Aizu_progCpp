#include <iostream>
#include <string>
#include <list>

bool compare(const std::string&, const std::string&);

int main(){
  std::list<std::string> IDs;
  std::string a;
  while(std::cin >> a){
    IDs.push_back(a);
  }
  IDs.sort(compare);

  std::list<std::string>::iterator ite = IDs.begin();
  while(ite != IDs.end()){
    std::cout << *ite << std::endl;
    ++ite;
  }
  return 0;
}

bool compare(const std::string& s1, const std::string& s2){
  return (s1 > s2);
}
