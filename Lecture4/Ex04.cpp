/*
    Ex04.cpp
    概要:./a.out < list2.txt でtxtファイルを読み込んで表示。構造体を使って情報を整理。
    Author:Ueta Kento
    Date:2021-10-21
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <stdexcept>

struct Student_info{
  std::string First_name;
  std::string Last_name;
  std::string ID;
  double Midterm;
  double Final;
  std::vector<double> Exercise;
};

std::string frame1(int, int);
std::istream& read(std::istream&, Student_info&);
std::istream& read_hw(std::istream&, std::vector<double>&);
double median(std::vector<double>);
double grade(double, double, const std::vector<double>&, double&, double&, double&);
bool compare(const Student_info&, const Student_info&);
/*const std::vector<double>& */
int main(){
  const int const_id = 11;
  const int const_first = 14;
  const int const_last = 14;
  const int const_point = 7;
  int counter = 0;

  std::vector<Student_info> students;
  Student_info record;
  while(read(std::cin, record)){
    students.push_back(record);
  }

  std::sort(students.begin(), students.end(), compare);
  double total, student_median, sum, average;

  const std::string line1(frame1(const_first,1) + frame1(const_last,1) + frame1(const_id,1)
                        + frame1(const_point,1) + frame1(const_point,1) + frame1(const_point,1) + frame1(const_point,1) + "+");

  const std::string line2(frame1(const_first,2) + frame1(const_last,2) + frame1(const_id,2)
                        + frame1(const_point,2) + frame1(const_point,2) + frame1(const_point,2) + frame1(const_point,2) + "+");

  std::cout << line1 << std::endl;
  for(int i = 0; i != students.size(); i++){
    counter++;
    try{
      total = grade(students[i].Midterm, students[i].Final, students[i].Exercise, student_median, sum, average);
      std::cout <<"|  "<< students[i].First_name << frame1(const_first - students[i].First_name.size(), 3)
      << "|  " << students[i].Last_name << frame1(const_last - students[i].Last_name.size(), 3)
      << "|  " << students[i].ID << frame1(const_id - students[i].ID.size(), 3)
      << "| " << std::fixed << std::setprecision(1) << std::setw(5) << sum << " "
      << "| " << std::setw(5) << average << " "
      << "| " << std::setw(5) << student_median << " "
      << "| " << std::setw(5) << total << " |" << std::endl;
    }catch(std::domain_error){
      std::cout <<"|  "<< students[i].First_name << frame1(const_first - students[i].First_name.size(), 3)
      << "|  " << students[i].Last_name << frame1(const_last - students[i].Last_name.size(), 3)
      << "|  " << students[i].ID << frame1(const_id - students[i].ID.size(), 3)
      << "| " << "no exercises" << std::endl;
    }
    if((counter % 5) == 0){
      std::cout << line2 << counter << std::endl;
    }
  }
  std::cout << line1 << std::endl;
  return 0;
}


std::istream& read(std::istream& is, Student_info& s){
  is >> s.ID >> s.Last_name >> s.First_name;
  is >> s.Midterm >> s.Final;
  read_hw(is, s.Exercise);
  return is;
}


std::istream& read_hw(std::istream& is, std::vector<double>& v){
  if(is){
    double x;
    v.clear();
    while(is >> x){
      v.push_back(x);
    }
    is.clear();//while文で発生したエラーの跡を消す
  }
  return is;//これによってisが空だった場合にfolseを返す。
}


double median(std::vector<double> v){
  double y;
  if(v.size() == 0){
    throw std::domain_error("配列の要素数が0です。");//例外処理
  }
  std::sort(v.begin(), v.end());
  if(v.size()%2 == 0){
    return (v[v.size() / 2 - 1] + v[v.size() / 2]) / 2;
  }else{
    return v[v.size() / 2];
  }
}

/*
  const std::vector<double>& hwはhwの本体の値をコピーせず、本体を直接持ってきているが、
  constによって本体の値を変えないようにしている。
  std::vector<double> hwだとhwをコピーした値を使うので本体の値は変わらないが、
  コピーをするので時間と容量が余計にかかる。
*/
double grade(double struct_medterm, double struct_final, const std::vector<double>& hw,
              double& student_median, double& sum, double& average){
                if(hw.size() == 0){
                  throw std::domain_error("配列の要素数が0です。");//例外処理
                }
                student_median = median(hw);
                sum = 0;
                for(int i = 0; i < hw.size(); i++){
                  sum += hw[i];
                }
                average = sum / hw.size();
                return 0.2 * struct_medterm + 0.4 * struct_final + 0.4 * student_median;
              }

bool compare(const Student_info& x, const Student_info& y){
  if(x.Last_name != y.Last_name){
    return (x.Last_name < y.Last_name);
  }else{
    return (x. First_name < y.First_name);
  }
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
