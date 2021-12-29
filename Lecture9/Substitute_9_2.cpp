#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <stdexcept>

class Student_info{
public:
  Student_info();
  Student_info(std::istream&);
  std::string get_first_name() const {return First_name;};
  std::string get_last_name() const {return Last_name;};
  std::string get_id() const {return ID;};
  double get_midterm() const {return Midterm;};
  double get_final() const {return Final;};
  double get_ex() const {return Ex;};
  double get_total() const {return Total;};
  double get_median() const {return Median;};
  double get_average() const {return Average;};
  double get_sum() const {return Sum;};
  std::vector<double> get_exercise() const {return Exercise;};
  bool valid() const {return Exercise.empty();};
  std::istream& read(std::istream&);
  std::istream& read_hw(std::istream&);
  double median();
  void grade();
  // void calcu_total();
private:
  std::string First_name, Last_name, ID;
  double Midterm, Final, Ex, Total, Median, Average, Sum;
  std::vector<double> Exercise;
};
// bool compare(const Student_info&, const Student_info&);

Student_info::Student_info() : Midterm(0), Final(0){} // コンストラクタ
Student_info::Student_info(std::istream& is){read(is);} // 違うパターンのコンストラクタ
/*
初期化処理を行う特別なメンバ関数がコンストラクタで、コンストラクタの名前は，クラス名と同じ。
引数の型や個数に応じて，複数のコンストラクタを定義可能。
• Student_info s1;
– 変数を宣言するだけ，データは不定
• Sudent_info s2(s1270151);
– 変数を宣言し，()からデータを読み込み，その値で初期化。今回は初期化する際にread関数を使ってる。
*/
std::istream& Student_info::read(std::istream& is){
  is >> ID >> Last_name >> First_name;
  is >> Midterm >> Final;
  read_hw(is);
  return is;
}
std::istream& Student_info::read_hw(std::istream& is){
  if(is){
    double x;
    Exercise.clear();
    while(is >> x){
      Exercise.push_back(x);
    }
    is.clear();//while文で発生したエラーの跡を消す
  }
  return is;//これによってisが空だった場合にfolseを返す。
}

double Student_info::grade(){
  /*
  if(Exercise.size() == 0){
    throw std::domain_error("配列の要素数が0です。"); // 例外処理
  }
  */
  Median = median();
  Sum = 0.0;
  for(int i = 0; i < Exercise.size(); i++){
    Sum += Exercise[i];
  }
  Average = Sum / Exercise.size();
  Total = 0.2 * Midterm + 0.4 * Final + 0.4 * Median;
  // return ::grade(Midterm, Final, Exercise);
}

double Student_info::median(){
  /*
  if(Exercise.size() == 0){
    throw std::domain_error("配列の要素数が0です。");//例外処理
  }
  */
  std::sort(Exercise.begin(), Exercise.end());
  if(Exercise.size()%2 == 0){
    return (Exercise[Exercise.size() / 2 - 1] + Exercise[Exercise.size() / 2]) / 2;
  }else{
    return Exercise[Exercise.size() / 2];
  }
}



std::string frame1(int, int);
bool compare(const Student_info&, const Student_info&);


int main(){
  const int const_id = 11;
  const int const_first = 14;
  const int const_last = 14;
  const int const_point = 7;
  int counter = 0;

  std::vector<Student_info> students;
  Student_info record;
  while(record.read(std::cin)){
    students.push_back(record);
  }

  std::sort(students.begin(), students.end(), compare);
  for(int i = 0; i != students.size(); i++){

      students[i].grade();
      std::cout << students[i].first_name() << " " << students[i].last_name() << " " << students[i].id()
      << " " << std::fixed << std::setprecision(1) << std::setw(5) << students[i].median()
      << " " << std::setw(5) << students[i].total()
      << " " << std::endl;
  }

  return 0;
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

bool compare(const Student_info& x, const Student_info& y){
  if(x.last_name() != y.last_name()){
    return (x.last_name() < y.last_name());
  }else{
    return (x. first_name() < y.first_name());
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
