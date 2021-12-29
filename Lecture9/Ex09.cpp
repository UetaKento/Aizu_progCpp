#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <stdexcept>

class Student_info{
public:
  Student_info();
  Student_info(std::istream&);
  std::string first_name() const {return First_name;};
  std::string last_name() const {return Last_name;};
  std::string id() const {return ID;};
  double midterm() const {return Midterm;};
  double final() const {return Final;};
  double ex() const {return Ex;};
  double total() const {return Total;};
  std::vector<double> exercise() const {return Exercise;};
  bool valid() const {return !Exercise.empty();};
  std::istream& read(std::istream&);
  std::istream& read_hw(std::istream&);
  double median();
  double grade();
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
  if(Exercise.size() == 0){
    throw std::domain_error("配列の要素数が0です。"); // 例外処理
  }
  Median = median();
  Sum = 0.0;
  for(int i = 0; i < Exercise.size(); i++){
    Sum += Exercise[i];
  }
  Average = Sum / Exercise.size();
  return 0.2 * Midterm + 0.4 * Final + 0.4 * Median;
  // return ::grade(Midterm, Final, Exercise);
}

double Student_info::median(){
  double y;
  if(Exercise.size() == 0){
    throw std::domain_error("配列の要素数が0です。");//例外処理
  }
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
  const std::string line1(frame1(const_first,1) + frame1(const_last,1) + frame1(const_id,1)
                        + frame1(const_point,1) + frame1(const_point,1) + frame1(const_point,1) + frame1(const_point,1) + "+");

  const std::string line2(frame1(const_first,2) + frame1(const_last,2) + frame1(const_id,2)
                        + frame1(const_point,2) + frame1(const_point,2) + frame1(const_point,2) + frame1(const_point,2) + "+");

  std::cout << line1 << std::endl;

  for(int i = 0; i != students.size(); i++){
    counter++;
    try{
      students[i].Total = students[i].grade();
      std::cout <<"|  "<< students[i].First_name << frame1(const_first - students[i].First_name.size(), 3)
      << "|  " << students[i].Last_name << frame1(const_last - students[i].Last_name.size(), 3)
      << "|  " << students[i].ID << frame1(const_id - students[i].ID.size(), 3)
      << "| " << std::fixed << std::setprecision(1) << std::setw(5) << students[i].Total << " "
      << "| " << std::setw(5) << students[i].Average << " "
      << "| " << std::setw(5) << students[i].Median << " "
      << "| " << std::setw(5) << students[i].Total << " |" << std::endl;
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
