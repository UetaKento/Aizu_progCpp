/*
    Ex02.cpp
    概要:./a.out < list2.txt でtxtファイルを読み込んで表示。
    Author:Ueta Kento
    Date:2021-10-7
*/

#include <iostream>
#include <string>
std::string frame1(int, int);

int main(){
  //const std::int id=8; とするとエラー
  const int const_id = 10;
  const int const_first = 14;
  const int const_last = 14;
  int counter = 0;
  std::string id("");
  std::string first("");
  std::string last("");
  const std::string line1(frame1(const_first,1) + frame1(const_last,1) + frame1(const_id,1) + "+");
  const std::string line2(frame1(const_first,2) + frame1(const_last,2) + frame1(const_id,2) + "+");

  std::cout << line1 << std::endl;
  while(std::cin >> id >> first >> last ){
    //std::cout << const_first - first.size() << std::endl;
    // first << frame1(const_first - first.size(), 3)
    counter++;
    std::cout << "| " << last << frame1(const_last - last.size(), 3)
    << "| " << first << frame1(const_first - first.size(), 3)
    << "| " << id << frame1(const_id - id.size(), 3)
    << "|" << std::endl;
    if((counter % 5) == 0){
      std::cout << line2 << counter << std::endl;
    }
  }
  std::cout << line1 << std::endl;

  return 0;
}

std::string frame1(int count, int version){
  std::string a("+");
  std::string b("");
  if(version == 1){
    for(int i = 0; i < count; i++){
      a += '=';
    }
  }else if(version == 2){
    for(int i = 0; i < count; i++){
      a += '-';
    }
  }else if(version == 3){
    for(int i = 1; i < count; i++){
      b += ' ';
    }
    a = b;
  }
  return a;
}
