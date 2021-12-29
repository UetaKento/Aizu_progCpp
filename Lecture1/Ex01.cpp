/*
    Ex01.cpp
    概要:アスタリスクをフレームとして、名前を表示する。
    Author:Ueta Kento
    Date:2021-10-4
*/
#include <iostream>
#include <string>

int main(){
  std::string first_name, meddle_name, last_name;
  std::cout << "Please input your first name" << std::endl;
  //std::string FirstName;
  std::cin >> first_name;
  std::cout << "Please input your middle name" << std::endl;
  std::cin >> meddle_name;
  std::cout << "Please input your last name" << std::endl;
  std::cin >> last_name;

  const std::string greeting(" Hello, " + first_name +" "+ meddle_name +" "+ last_name + " ! ");
  const std::string asterisks1(greeting.size(),'*');
  //const std::string asterisks2("'*' + asterisks1 + '*'");
  const std::string spaces(greeting.size(),' ');

  std::cout << "*" << asterisks1 << "*" << std::endl;
  std::cout << "*" << spaces << "*" << std::endl;
  std::cout << "*" << greeting << "*" << std::endl;
  std::cout << "*" << spaces << "*" << std::endl;
  std::cout << "*" << asterisks1 << "*" << std::endl;
  return 0;
}
/*
5.名前が極端に長いときの動作を確認
結果:フレームが横長になった。
6.名前が文字が英語以外のときの動作を確認
結果:ひらがなや漢字を打つとフレームの長さが短くなった。
*/
