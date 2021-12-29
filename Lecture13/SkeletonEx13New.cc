/*
    SkeltonEx13.cc
    C++ source code for Ex-13, Prog C++2
        Author: Keitaro Naruse
        Date: 2020-11-16
*/
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <stdexcept>
#include <iomanip>

/*
    Core class
        Provide core functions for student information
*/
class Core{
    //  Put code below
  public:
    Core();
    Core(std::istream&);
    std::string name() const ;
    virtual double grade();
    virtual double median();
    virtual std::istream& read(std::istream&);
    friend class Student_info;
  protected:
    // std::istream& read_common( std::istream& );
    std::istream& read_hw(std::istream&);
    double midterm, final;
    std::vector<double> homework;
    virtual Core* clone( ) const { return new Core(*this); }
  private:
    std::string n;
};

std::string Core::name( ) const { return n; }

double Core::grade( )
{
  double Median,Sum,Total;
  if(homework.size() == 0){
    return 0;
  }
  Median = median();
  Sum = 0.0;
  for(int i = 0; i < homework.size(); i++){
    Sum += homework[i];
  }
  // Average = Sum / homework.size();
  Total = 0.2 * midterm + 0.4 * final + 0.4 * Median;
  return Total;
}

double Core::median()
{
  if(homework.size() == 0){
    return 0;
  }
  std::sort(homework.begin(), homework.end());
  if(homework.size()%2 == 0){
    return (homework[homework.size() / 2 - 1] + homework[homework.size() / 2]) / 2;
  }else{
    return homework[homework.size() / 2];
  }
}

std::istream& Core::read ( std::istream& in )
{
  in >> n >> midterm >> final;
  read_hw( in );
  return in;
}
/*
std::istream& Core::read_common( std::istream& in )
{
  in >> n >> midterm >> final;
  return in;
}
*/
std::istream& Core::read_hw( std::istream& in )
{
  if(in){
    double x;
    homework.clear();
    while(in >> x){
      homework.push_back(x);
    }
    in.clear();//while文で発生したエラーの跡を消す
  }
  return in;//これによってisが空だった場合にfolseを返す。
}


/*
    Grad class
        Provide a class for a graduate student
*/
class Grad: public Core {
    //  Put code below
  public:
    Grad();
    Grad(std::istream&);
    double grade() const;
    std::istream& read(std::istream&);
  protected:
    virtual Core* clone( ) const { return new Grad (*this); }
  private:
    double thesis;
};

/*
    Student_info class
        Provide a hundle class
*/
class Student_info{
    //  Put code below
    //  Student_info class should have valid() function
  private:
    Core *cp;
  public:
    Student_info() : cp(0) {}
    Student_info(std::istream& is) : cp (0) {read(is);}
    Student_info(const Student_info& is);
    ~Student_info() {delete cp;}
    std::istream& read( std::istream& );
    std::string name() const {
      if(cp){
        return cp->name();
      }else {
        throw std::runtime_error("uninitialized");
      }
    }
    static bool compare(const Student_info& s1, const Student_info& s2){
      return s1.name() < s2.name();
    }
    bool valid(){
      if (cp->median() == 0) {
        return false;
      }else{
        return true;
      }
    }
    double grade() {
      if(cp){
        return cp->grade();
      }else {
        throw std::runtime_error("uninitialized");
      }
    }
};

std::istream& Student_info::read( std::istream& is)
{
  delete cp;
  char ch;
  is >> ch;
  if(ch == 'u') {
    cp = new Core( is );
  } else {
    cp = new Grad( is );
  }
  return is;
}

Student_info::Student_info( const Student_info& s) : cp( 0 )
{
  if( s.cp ) cp = s.cp -> clone( );
}

/*
Student_info& Student_info::operator=(const Student_info& s)
{
  if(&s != this) {
    delete cp;
    if(s.cp){
      cp = s.cp ;
    }
    else{
      cp = 0;
    }
  }
  return *this;
}
*/

/*
    main()
*/
int main(int argc, char* argv[])
{
    std::vector<Student_info> students;
    Student_info record;
    std::string::size_type maxlen = 0;

    while( record.read(std::cin) ){ //最初にStudent_info型のreadが動く。
        maxlen = std::max( maxlen, record.name().size() );
        students.push_back( record );
    }

    std::sort(students.begin(), students.end(), Student_info::compare);

    for(std::vector<Student_info>::size_type i = 0; i != students.size(); ++i){
        std::cout << students[i].name()
	      << std::string(maxlen + 1 - students[i].name().size(), ' ');
        if( students[i].valid() ){
            double final_grade = students[i].grade();
            std::streamsize prec = std::cout.precision();
            std::cout << std::setprecision(3) << final_grade
		    << std::setprecision(prec);
        }
        else{
            std::cout << "Caanot evaluate";
        }
        std::cout << std::endl;
    }

    return 0;
}
