#include <iostream>
#include <iomanip>
#include <string>
#include <list>
#include <cctype>

struct WordCount{
  std::string Word;
  int Count;
};

bool compare(const WordCount&, const WordCount&);
std::string block(int);

int main(){
  const int space = 18;
  std::string s;
  std::string tmp;
  std::list<WordCount> words;
  WordCount wct;
  /*外側のwhileループ。sample5.txtを読み込んでlistに追加してなかったらlistに追加する。*/
  while (std::cin >> s) {
    int isFound = 0;
    std::list<WordCount>::iterator iter = words.begin();

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
    /*
    次のswitc文はフォールスルー(fall through/落ちる)というbreakがない文。
    これにより、case 1の処理の後、case 2の処理も実行される。


    switch (s[s.size() - 1]) {
      case '.':
      s = s.substr(0,s.size() - 1);
      //break;
      case ',':
      s = s.substr(0,s.size() - 1);
      //break;
      case ')':
      s = s.substr(0,s.size() - 1);
      //break;
      case '\"':
      s = s.substr(0,s.size() - 1);
      //break;
      case '\'':
      s = s.substr(0,s.size() - 1);
      //break;
    }


    switch (s[0]) {
      case '(':
      s = s.substr(1,s.size() - 1);
      //break;
      case '\"':
      s = s.substr(1,s.size() - 1);
      //break;
      case '\'':
      s = s.substr(1,s.size() - 1);
      //break;
    }
    */

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

  words.sort(compare);
  std::list<WordCount>::iterator iter = words.begin();

  while (iter != words.end()) {
    std::cout << (*iter).Word << block(space - (*iter).Word.size()) << (*iter).Count << '\n';
    iter++;
  }

  return 0;
}


bool compare(const WordCount& x, const WordCount& y){
  if(x.Word != y.Word){
    return (x.Word < y.Word);
  }else{
    return (x.Word > y.Word);
  }
}

std::string block(int count){
  std::string a("");
  for(int i = 0; i < count; i++){
    a += ' ';
  }
  return a;
}
