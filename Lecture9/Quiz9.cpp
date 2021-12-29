#include <iostream>
#include <string>
using namespace std;
class WordCount{
public:
  WordCount() : Word(""), Count(0){
    ;
  }
  WordCount(const string& s, const int& k){
    Word = s;
    Count = k;
  }
  string word() const {
    return (Word);
  };

  int count() const {
    return(Count);
  }
  void word(const string& s){
    Word = s;
  }
  void count(const int& k){
    Count = k;
  }
private:
  string Word;
  int Count;
};
int main() {
  WordCount wc1, wc2("test2", 2);
  std::cout << wc1.word() << " " << wc1.count() <<
  std::endl; std::cout << wc2.word() << " " << wc2.count() << std::endl;
  wc1.word("test1");
  wc2.count(2);
  std::cout << wc1.word() << " " << wc1.count() << std::endl;
  std::cout << wc2.word() << " " << wc2.count() << std::endl;
  cout << "Normally terminated." << std::endl;
  return 0;
}
