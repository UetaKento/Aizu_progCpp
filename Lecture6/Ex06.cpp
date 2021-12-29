#include <iostream>
#include <iomanip>
#include <vector>
#include <cctype>
#include <iterator>
#include <string>
#include <algorithm>

struct WordCount{
  std::string Word;
  int Count;
};

struct URL{
  std::string Protocol;
  std::string Resource;
};


bool alpha_or_other(const WordCount&);
bool length_compare(const WordCount&);
bool compare(char);
std::string block(int);

double global_ave = 0;

int main(){
  //const int space = 18;
  std::string s;
  std::string tmp;
  std::vector<WordCount> words;
  std::vector<URL> urls;
  WordCount wct;
  URL lru;
  /*外側のwhileループ。sample5.txtを読み込んでlistに追加してなかったらlistに追加する。*/
  while (std::cin >> s) {
    int isFound = 0;
    std::vector<WordCount>::iterator iter = words.begin();
    /*
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
    */

    for(std::string::size_type i = 0; i != s.size(); ++i ) {
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
      if(s[s.size() - 1] == '?'){
        s = s.substr(0,s.size() - 1);
      }

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

  std::vector<WordCount>::iterator iter;
  iter = stable_partition(words.begin(), words.end(), alpha_or_other);

  iter = words.begin();
  std::string sep = "://";
  std::string::iterator url_iter;
  double sum = 0;

  while (iter != words.end()) {
    url_iter = search((*iter).Word.begin(), (*iter).Word.end(), sep.begin(), sep.end());
    if ((*url_iter) == ':') {
      copy((*iter).Word.begin(), url_iter, back_inserter(lru.Protocol));
      copy(url_iter + 3, (*iter).Word.end() + 1, back_inserter(lru.Resource));
      urls.push_back(lru);
      words.erase(iter);
    }
    sum += (*iter).Count;
    iter++;
  }
  global_ave = sum / words.size();

  // iter = stable_partition(words.begin(), words.end(), length_compare);

  /*
  std::string::iterator iterator;
  // srcからsepの文字列に位置を探す
  iterator = search(src.begin(), src.end(), sep.begin(), sep.end());
  // sepが含まれているので，iterは「:」の位置を指すことになる
  std::cout << *(iterator) << '\n';
  // std::cout << *(iterator) << '\n' を実行すると : が表示される。
  if (*(iterator) != ':') {
    std::cout << "abc" << '\n';
  }
  */


  iter = words.begin();
  while (iter != words.end()) {
    std::cout << (*iter).Word << " " << (*iter).Count << '\n';
    iter++;
  }
  std::cout << global_ave << 'n';


  /*
  char c = 'b';
  bool tf = isalpha(5);
  std::cout << std::boolalpha << tf << '\n';
  */
  return 0;
}

bool alpha_or_other(const WordCount& wordc){
  std::string s = wordc.Word;
  for(std::string::size_type i = 0; i != s.size(); ++i ) {
    if(compare(s[i])){
      return false;
    }
  }
  return true;
}

bool length_compare(const WordCount& wordc){
  return (global_ave < wordc.Count);
}

bool compare(char c){
  return (!isalpha(c));
}


std::string block(int count){
  std::string a("");
  for(int i = 0; i < count; i++){
    a += ' ';
  }
  return a;
}
