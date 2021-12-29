/*
    SkeltonEx08.cc
        C++ source code for Ex-8, Prog C++
        Author: Keitaro Naruse
        Date: 2020-11-12
*/
#include <string>
#include <iostream>
#include <iterator>
#include <vector>

//  Prototype
bool isEven(int);

//  Put prototype for my_search, here
template< class ForwardIterator1, class ForwardIterator2 >
ForwardIterator1 my_search( ForwardIterator1 b, ForwardIterator1 e, ForwardIterator2 b2, ForwardIterator2 e2 );

template< class InputIterator, class OutputIterator >
OutputIterator my_copy( InputIterator b, InputIterator e, OutputIterator d );

template< class BidirectionalIterator, class Predicate >
BidirectionalIterator my_partition( BidirectionalIterator b, BidirectionalIterator e, Predicate p);

/*
    main()
        main function
*/
int main(int argc, char *argv[])
{
    std::string
    src1 = "https://www.u-aizu.ac.jp/~naruse",
    src2 = "/ProgC++2020/index.html",
    src3 = "another",
    query1 = "://";
    std::string::iterator i;
    std::vector<int> data;
    std::vector<int>::iterator sep;

    // my_search() test1
    // Try to search query1 in src1
    i = my_search( src1.begin(), src1.end(), query1.begin(), query1.end() );
    if( i == src1.end() ){
        std::cout << "[" << query1 << "]" << " is NOT found in [" << src1 << "]" << std::endl;
    }
    else{
        std::cout << "[" << query1 << "]" << " is found at [" << std::string( i, src1.end() ) << "]"  << std::endl;
    }

    //  my_search() test2
    //  Try to search query1 in src2
    i = my_search( src2.begin(), src2.end(), query1.begin(), query1.end() );
    if( i == src2.end() ){
      std::cout << "[" << query1 << "]" << " is NOT found in [" << src2 << "]" << std::endl;
    }
    else{
      std::cout << "[" << query1 << "]" << " is found at [" << std::string( i, src2.end() ) << "]"  << std::endl;
    }

    //  my_copy() test1
    //  copy src2 at the end of src1
    my_copy( src2.begin(), src2.end(), back_inserter(src1) );
    std::cout << src1 << std::endl;

    //  my_copy() test2
    //  copy src3 from the 24th letter of src1
    i = my_copy( src3.begin(), src3.end(), src1.begin() +  24);
    std::cout << src1 << std::endl;
    std::cout << "Following letters are [";
    while( i != src1.end() ){
        std::cout << *i;
        ++i;
    }
    std::cout << "]" << std::endl;

    //  Test for my_partition
    for(int j = 0; j < 10; j++){
        data.push_back(j);
        std::cout << data[j] << " ";
    }
    std::cout << std::endl;

    sep = my_partition( data.begin(), data.end(), isEven );
    for( int j = 0; j < data.size(); ++j ){
        std::cout << data[j] << " ";
    }
    std::cout << std::endl << *sep << std::endl;

    for( int j = 0; j < data.size(); ++j ){
        data[j ] = 0;
        std::cout << data[j] << " ";
    }
    sep = my_partition( data.begin(), data.end(), isEven );
    std::cout << std::endl << *sep << std::endl;

    for( int j = 0; j < data.size(); ++j ){
        data[j ] = 1;
        std::cout << data[j] << " ";
    }
    sep = my_partition( data.begin(), data.end(), isEven );
    std::cout << std::endl << *sep << std::endl;

    return(0);
}

/*
    my_search()
        Generic function work same as search in C++ standard library
*/
 template<class ForwardIterator1, class ForwardIterator2>
 ForwardIterator1 my_search( ForwardIterator1 b, ForwardIterator1 e, ForwardIterator2 b2, ForwardIterator2 e2 )
 {
   /*
   while (b != e) {
     if (b == b2) {
       while (b2 != e) {
         if (b != b2) {
           b++;
           break;
         }else{
           b++;
           b2++;
         }
       }
     }else{
       b++;
     }
   }
   */

   for ( ; b != e; ++b) {
     ForwardIterator1 cp = b; //ForwardIteratorなので、間違いが会ったときに後ろに戻れない可能性がある。だからコピーを用意して、コピーで同じものがあるか検査していく。
     ForwardIterator2 cp2 = b2;
     while (true) {
       if (cp2 == e2) return b; // 2.検索している文字の最後まで一致している場合、コピー元のbを返す。
       if (cp == e) return e; // 3.2に同じ。
       if (*(cp) != *(cp2)) break; // 1.cp1とcp2の中身が同じ間のみwhileループで++cp1,++cp2する。abcbgdからbdを探すと仮定した場合、外側のforはaからdまで動き、中のwhileはabcbgd一つ一つがbdと一致するかのチェックしている。
       ++cp, ++cp2;
     }
   }
   return b;
 }


/*
    my_copy()
        Generic function work same as copy in C++ standard library
 */
template< class InputIterator, class OutputIterator >
OutputIterator my_copy( InputIterator b, InputIterator e, OutputIterator d )
{
    while (b != e) {
      *d = *b; //c++日本語リファレンスでは、*d++ = *b++;のみ。これは*d = *bをした後に、d++,b++を実行している。
      d++;
      b++;
    }
    return d;

}

template< class BidirectionalIterator, class Predicate >
BidirectionalIterator my_partition( BidirectionalIterator b, BidirectionalIterator e, Predicate p)
{
    //  Put source code below
    //  You can use std::iter_swap(i, j);
    //  for exchanging the contents of iterators i and j
    //  Or you can use std::swap(i, j);
    //  for exchanging object i and j
    BidirectionalIterator cut = b; //trueとfalseの境界線のイテレータをリターンするので用意。
    while (b != e) {
      if(p(*b) == true){
        std::iter_swap(cut, b); //2.停止させた境界線のイテレータと動いていたbをスワップ。
        cut++; //1.p(*b) == false の時だけ境界線のイテレータを停止させる。
      }
      b++;
    }
    return cut;
}

bool isEven(int num)
{
    if( num % 2 == 0 ){
        return( true );
    }
    return( false );
}
