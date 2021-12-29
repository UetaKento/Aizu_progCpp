/*
    Ex03.cpp
    概要:./a.out < list2.txt でtxtファイルを読み込んで表示。構造体を使って情報を整理。
    Author:Ueta Kento
    Date:2021-10-18
*/
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
//#include <algorithm>
std::string frame1(int, int);

//学生の持つ様々な情報を構造体にすることで学生の情報をその学生の属性にした。演習の結果はvector型。
struct student{
  std::string struct_id;
  std::string struct_first_name;
  std::string struct_last_name;
  int struct_mid_exam;
  int struct_final_exam;
  std::vector<float> struct_exercises;
  float struct_sum;
  float struct_average;
  float struct_median;
  float struct_evaluation;
};

int main(){
  std::vector<student> s;//構造体にした学生の情報をvector型にして、一人一人を分かりやすくした。
  s.clear();
  const int const_id = 11;
  const int const_first = 14;
  const int const_last = 14;
  const int const_point = 7;

  student a;//vector型にした構造体にs.push_back(a)するためのやつ。
  std::string id("");
  std::string first("");
  std::string last("");
  float mid_exam;
  float final_exam;
  float exercises;
  int counter = 0;

  const std::string line1(frame1(const_first,1) + frame1(const_last,1) + frame1(const_id,1)
                          + frame1(const_point,1) + frame1(const_point,1) + frame1(const_point,1) + frame1(const_point,1) + "+");
  const std::string line2(frame1(const_first,2) + frame1(const_last,2) + frame1(const_id,2)
                          + frame1(const_point,2) + frame1(const_point,2) + frame1(const_point,2) + frame1(const_point,2) + "+");

  std::cout << line1 << std::endl;
  //学籍番号から期末試験の点数までの長さはどの学生も同じなのでEOFまで読み込み。
  while(std::cin >> id >> first >> last >> mid_exam >> final_exam ){
    a.struct_id = id;
    a.struct_first_name = first;
    a.struct_last_name = last;
    a.struct_mid_exam = mid_exam;
    a.struct_final_exam = final_exam;
    //演習点は学生によって長さが違うので演習点を一つずつ読み込み、演習点に-1が入ったらbreakして外のwhileへ。
    while(std::cin >> exercises){
      if(exercises == -1){
        break;
      }
      a.struct_exercises.push_back(exercises);//構造体の属性にあるvector型のstruct_exercisesにpush。
      a.struct_sum = a.struct_sum + exercises;
      a.struct_average = a.struct_sum / a.struct_exercises.size();
    }

    std::sort(a.struct_exercises.begin(), a.struct_exercises.end());

    if(a.struct_exercises.size() == 0){
      a.struct_average = 0;
      a.struct_median = 0;
    }else if((a.struct_exercises.size() % 2) == 1){
      a.struct_median = a.struct_exercises[a.struct_exercises.size() / 2];
    }else if((a.struct_exercises.size() % 2) == 0){
      a.struct_median = (a.struct_exercises[a.struct_exercises.size() / 2 - 1] +
                         a.struct_exercises[a.struct_exercises.size() / 2] ) / 2;
    }

    a.struct_evaluation = a.struct_mid_exam * 2 / 10 + a.struct_final_exam * 4 / 10 + a.struct_median * 4 / 10;

    s.push_back(a);//vector型にした構造体にpush。
    a.struct_exercises.clear();//これをしないと学生全員分の演習点が同じstruct_exercisesにpushされ続ける。学生の区別のために必要。
    a.struct_sum = 0;
  }

  /*表示に関する部分*/
  //s.size()は学生の人数。
  for(int i = 0; i < s.size(); i++){
    counter++;
    //s[i].struct_exercises.size()はその学生の演習点の長さ。
    std::cout << "|  " << s[i].struct_last_name << frame1(const_last - s[i].struct_last_name.size(), 3)
    << "|  " << s[i].struct_first_name << frame1(const_first - s[i].struct_first_name.size(), 3)
    << "|  " << s[i].struct_id << frame1(const_id - s[i].struct_id.size(), 3)
    << "| " << std::fixed << std::setprecision(1) << std::setw(5) << s[i].struct_sum << " "
    << "| " << std::setw(5) << s[i].struct_average << " "
    << "| " << std::setw(5) << s[i].struct_median << " "
    << "| " << std::setw(5) << s[i].struct_evaluation << " |";
    std::cout << std::endl;
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
    for(int i = 2; i < count; i++){
      b += ' ';
    }
    a = b;
  }
  return a;
}
