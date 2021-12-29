#include <iostream>
#include <cctype>
#include <vector>
#include <string>

struct WordCount{
  std::string Word;
  int Count;
};

//std::istream& read(std::istream&, WordCount&);

int main(){
  std::string s;
  std::string tmp;
  std::vector<WordCount> words;
  WordCount wct;

  while (std::cin >> s) {
    int isFound = 0;
    std::vector<WordCount>::iterator iter = words.begin();

    if(s[s.size() - 1] == '.'){
      s = s.substr(0,s.size() - 1);
    }
    if(s[s.size() - 1] == ','){
      s = s.substr(0,s.size() - 1);
    }
    if(s[0] == '('){
      s = s.substr(1,s.size() - 1);
    }
    if(s[s.size() - 1] == ')'){
      s = s.substr(0,s.size() - 1);
    }
    if(s[0] == '\"'){
      s = s.substr(1,s.size() - 1);
    }
    if(s[s.size() - 1] == '\"'){
      s = s.substr(0,s.size() - 1);
    }
    if(s[0] == '\''){
      s = s.substr(1,s.size() - 1);
    }
    if(s[s.size() - 1] == '\''){
      s = s.substr(0,s.size() - 1);
    }

    for(std::string::size_type i = 0; i != s.size(); ++i ) {
      s[i] = tolower(s[i]);
    }

    while (iter != words.end()) {
      if((*iter).Word == s){
        isFound = 1;
        (*iter).Count++;
        break;
      }
      iter++;
    }

    if(isFound == 0){
      wct.Word = s;
      wct.Count = 1;
      words.push_back(wct);
    }

  }

  std::vector<WordCount>::iterator iter = words.begin();
  //iter = words.begin();

  while (iter != words.end()) {
    std::cout << iter->Word << " " << iter->Count << '\n';
    iter++;
  }

  return 0;
}

/*
std::vector<WordCount> words;
std::vector<WordCount>::iterator iter = words.begin();
WordCount w;
w.Word = "ccc";
w.Count = 1;
words.push_back(w);
iter++;
w.Word = "bbb";
w.Count = 3;
words.push_back(w);
iter++;
iter = words.begin();
int i = 0;
while (iter != words.end()) {
  std::cout << iter->Word << iter->Count << '\n';
  iter++;
}
*/
