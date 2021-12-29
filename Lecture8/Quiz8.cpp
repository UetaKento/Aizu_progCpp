#include <iostream>
#include <string>
#include <list>

template <class T>
void swap(T&, T&);

int main(){
  std::list<std::string> words;
  std::string word;
  while(std::cin >> word){
    words.push_back(word);
  }

  std::list<std::string>::iterator iter = words.begin();
  std::cout << "Before Swap" << '\n';
  while (iter != words.end()) {
    std::cout << (*iter) << " ";
    iter++;
  }
  std::cout << '\n';

  std::list<std::string>::iterator iter_curr = words.begin();
  std::list<std::string>::iterator it_prev;
  while (iter_curr != words.end()) {
    it_prev = iter_curr;
    if (++iter_curr == words.end()) {
      break;
    }
    swap((*it_prev), (*iter_curr));
    ++iter_curr;
  }

  iter = words.begin();
  std::cout << "After Swap" << '\n';
  while (iter != words.end()) {
    std::cout << (*iter) << " ";
    iter++;
  }
  std::cout << '\n';
  return 0;
}

template <class T>
void swap(T& a, T& b){
  T temp = a;
  a = b;
  b = temp;
}
