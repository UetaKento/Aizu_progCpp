#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <iterator>

std::vector<std::string> split(std::string);
bool not_space(char);
bool space(char);

int main(){
  std::map<std::string, std::vector<int> > counters;
  std::string search_word;
  std::string s;
  std::vector<std::string> splited;
  int row = 0; //行数の格納

  std::cin >> search_word;
  while(std::getline(std::cin, s)) {
    splited = split(s);
    for(int i = 0; i < splited.size(); i++){
        counters[splited[i]].push_back(row);
    }
    row++;
  }

  /*
  for(std::map<std::string, int >::iterator iter = counters.begin(); iter != counters.end(); ++iter)  {
    std::cout << iter -> first << " " << iter -> second << std::endl;
  }
  */

  std::cout << search_word << " is appeared at ";
  for(int i = 0; i < counters[search_word].size(); i++){
      std::cout << counters[search_word][i] << " ";
  }
  std::cout << std::endl;

  return 0;
}


std::vector<std::string> split(std::string str){
  std::vector<std::string> store;
  std::string::iterator i = str.begin();
  std::string::iterator j;

  for(std::string::size_type i = 0; i != str.size(); ++i){
      if(str[i] == '.' || str[i] == ',' || str[i] == '\"' || str[i] == '(' || str[i] == ')' || str[i] == '?'){
          str[i] = ' ';
      }
      str[i] = tolower(str[i]);
  }

  while (j != str.end()) {
    std::string word;
    i = find_if(i, str.end(), not_space);
    j = find_if(i, str.end(), space);

    copy(i, j, back_inserter(word));
    store.push_back(word);
    //std::cout << word << '\n';
    i = j;
  }

  return store;
}



bool not_space(char c){
  //spaceだったらfalseを返す。not_spaceだったらtrueを返す。
  return (!isspace(c));
}

bool space(char c){
  //spaceだったらtrueを返す。
  return (isspace(c));
}
