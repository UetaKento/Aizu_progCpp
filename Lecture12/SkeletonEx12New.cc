/*
    SkeltonEx12.cc
        Skelton of C++ source code for Ex-12, Prog-C++
        Author: Keitaro Naruse
        Date: 2020-11-16
*/
#include <iostream>
#include <ctype.h>
#include "SkeletonEx11New.cc"
// #include <algorithm>

//  Put class Vec here
//  You can import the source file in ex11

class Str	{
public:
    friend std::istream& operator >> (std::istream&, Str&);
    typedef Vec<char>::size_type size_type;
    Str() {};
    Str(size_type n, char c) : data(n, c) {};
    Str(const char* cp)	{
        //  Put source code here
        std::copy(cp, cp + std::strlen(cp), std::back_inserter(data));
    }
    template <class In> Str(In b, In e)	{
        //  Put source code here
        std::copy(b, e, std::back_inserter(data));
    }
    char& operator[](size_type i) {
        //  Put source code here
        return data[i];
    };
    const char& operator[](size_type i) const {
        //  Put source code here
        return data[i];
    }
    size_type size() const {
        //  Put source code here
        return data.size();
    }
    Str& operator += (const Str& s){
        //  Put source code here
        std::copy(s.data.begin(), s.data.end(), std::back_inserter(data));
        return *this;
    }
    bool operator == (const Str& s) const {
        //  Put source code here
        if( size() != s.size() ){
          return false;
        }
        for( Str::size_type i = 0; i != size(); ++i ){
          if(data[i] != s[i]){
            return false;
          }
        }
        return(true);
    }
    bool operator != (const Str& s) const {
        //  Put source code here
        if( size() != s.size() ){
          return true;
        }
        for( Str::size_type i = 0; i != size(); ++i ){
          if(data[i] != s[i]){
            return true;
          }
        }
        return(false);
    }
    char* begin(){
        //  Put source code here
        return(data.begin());
    }
    char* end(){
        //  Put source code here
        return(data.end());
    }
private:
    Vec<char> data;
};
std::ostream& operator << (std::ostream&, const Str&);

std::ostream& operator << (std::ostream& os, const Str& s)
{
    //  Put source code here
    for(Str::size_type i = 0; i != s.size(); ++i){
      os << s[i];
    }
    return os;
}

std::istream& operator >> (std::istream& is, Str& s)
{
    //  Put source code here
    // 現在のデータを破棄, Vecクラスにclear()を実装する必要
    s.data.clear();
    // 空白を読んで破棄
    char c;
    while(is.get(c) && isspace(c)){}
    // 空白だったら何もしない
    if(is) {
      // このままでは，ここでコンパイルエラー
      // この演算子にprivateのメンバにアクセスさせる必要
      do s.data.push_back(c);
      while(is.get(c) && !isspace(c));
      // もし，空白を読み込んだら，ストリームに戻す
      if(is){
        is.unget();
      }
    }
    return is;
}

Str operator + (const Str& s, const Str& t)
{
    //  Put source code here
    Str r = s;
    r += t;
    return r;
}

int main(int argc, char* argv[])
{
    Str s1;
    Str s2(8, 'a');
    Str s3("Hello! How are you?");
    Str s4(s3.begin(), s3.end());

    std::cout << "s1:[" << s1 << "]" << std::endl;
    std::cout << "s2:[" << s2 << "]" << std::endl;
    std::cout << "s3:[" << s3 << "]" << std::endl;
    std::cout << "s4:[" << s4 << "]" << std::endl;
    if(s3 == s4){
        std::cout << "#1: s3 is same as s4" << std::endl;
    }
    else {
        std::cout << "#1: s3 is different from s4" << std::endl;
    }
    s4[0] = 'h';
    std::cout << "s4:[" << s4 << "]" << std::endl;
    if(s3 == s4){
        std::cout << "#2: s3 is same as s4" << std::endl;
    }
    else {
        std::cout << "#1: s3 is different from s4" << std::endl;
    }
    std::cout << "Finished" << std::endl;

    return 0;
}
