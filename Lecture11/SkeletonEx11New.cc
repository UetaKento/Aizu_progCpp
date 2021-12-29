/*
    SkeltonEx11.cc
        Skelton of C++ source code for Ex-11, Prog C++
        Author: Keitaro Naruse
        Date: 2020-11-16
*/

#include <memory>
#include <algorithm>
#include <iostream>

template<class T>
class Vec{
public:
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef size_t size_type;
    typedef T value_type;
    typedef T& reference;
    typedef const T& const_reference;
    Vec() { create(); };
    explicit Vec(size_type n, const T& val = T()) { create(n, val); };
    Vec(const Vec& v) { create( v.begin(), v.end() ); };
    Vec<T>& operator=(const Vec& rhs);
    ~Vec() { uncreate(); };
    T& operator[](size_type i) { return data[i]; };
    const T& operator[](size_type i) const { return data[i]; };
    void push_back( const T& val ) {
        if( avail == limit ){
            grow();
        }
        unchecked_append( val );
    }
    size_type size() const { return avail - data; };
    iterator begin() { return data; };
    const_iterator begin() const { return data; };
    iterator end() { return avail; };
    const_iterator end() const { return avail; };
    // void clear(){ uncreate(); };
private:
    iterator data;
    iterator avail;
    iterator limit;
    std::allocator<T> alloc;
    void create();
    void create(size_type, const T&);
    void create(const_iterator, const_iterator);
    void uncreate();
    void grow();
    void unchecked_append(const T&);
};

/*
    Vec<T>::operator=
        Assignment operator
*/
template <class T>
Vec<T>& Vec<T>::operator=(const Vec& rhs)
{
    //  Put source code below
    if(&rhs != this){ // 自己代入でなければ
      uncreate(); // 古い内容破棄して，
    }
    create(rhs.begin(), rhs.end()); // 新しい内容に
    return *this;
}

/*
    Vec<T>::create()
        Initialize function (default)
*/
template <class T>
void Vec<T>::create()
{
    //  Put source code below
    data = avail = limit = 0;
}

/*
    Vec<T>::create()
        Initialize function with size and value
*/
template <class T>
void Vec<T>::create(size_type n, const T& val)
{
    //  Put source code below
    data = alloc.allocate( n );
    limit = avail = data + n;
    std::uninitialized_fill(data, limit, val);
}

/*
    Vec<T>::create()
        Initialize function with iterators
*/
template <class T>
void Vec<T>::create(const_iterator i, const_iterator j)
{
    //  Put source code below
    data = alloc.allocate( j - i );
    limit = avail = std::uninitialized_copy( i, j, data );
}

/*
    Vec<T>::uncreate()
        Finalize function
*/
template <class T>
void Vec<T>::uncreate()
{
    //  Put source code below
    if(data) {
      // データを逆順に破棄
      iterator it = avail;
      while( it != data ){
        alloc.destroy(--it);
      }
      // 確保されていたメモリを開放
    }
    alloc.deallocate(data, limit - data);
    // ポインタを0にリセットし，空になったことを示す
    data = limit = avail = 0;
}

/*
    Vec<T>::grow()
        Increase data size
*/
template <class T>
void Vec<T>::grow()
{
    //  Put source code below
    // 今までの2倍の量のメモリを確保，その計算
    size_type new_size = std::max( 2 * (limit - data), ptrdiff_t(1) );
    // メモリの確保と既存の内容のコピー
    iterator new_data = alloc.allocate( new_size );
    iterator new_avail = std::uninitialized_copy( data, avail, new_data ); // これまで使っていたメモリ領域を開放
    uncreate();
    // 新しいメモリ領域を指すようにポインタをリセット
    data = new_data;
    avail = new_avail;
    limit = data + new_size;
}

/*
    Vec<T>::unchecked_append()
        Append data
*/
template <class T>
void Vec<T>::unchecked_append(const T& val)
{
    //  Put source code below
    alloc.construct(avail ++, val);
}

/*
    main()
*/
int main(int argc, char *argv[])
{
    Vec<int> c1;
    Vec<int> c2( 8 );
    Vec<int> c3( 4, 1 );
    Vec<int> c4( c3 );
    Vec<int>::iterator i;
    int j;

    //  Check for default constructor and iterator
    std::cout << "c1: #1" << std::endl;
    for(i = c1.begin(); i != c1.end(); ++i){
        std::cout << *i << " ";
    }
    std::cout << std::endl;

    //  Check for constructor with size, and operator[] for read
    std::cout << "c1: #2" << std::endl;
    c1.push_back( 0 );
    for( j = 0; j != c1.size(); ++j ){
        std::cout << c1[ j ] << " ";
    }
    std::cout << std::endl;

    //  Check for constructor with size
    std::cout << "c2: #1" << std::endl;
    for( i = c2.begin(); i != c2.end(); ++i ){
        std::cout << *i << " ";
    }
    std::cout << std::endl;

    //  Check for constructor with size and value
    std::cout << "c3: #1" << std::endl;
    for( j = 0; j != c3.size(); ++j ){
        std::cout << c3[ j ] << " ";
    }
    std::cout << std::endl;

    //  Check for constructor with another container
    std::cout << "c4" << std::endl;
    for( j = 0; j != c4.size(); ++j ){
    std::cout << c4[ j ] << " ";
    }
    std::cout << std::endl;

    //  Check for operator[] for write
    c3[0] = 0;
    c3[1] = 1;
    c3[2] = 2;
    c3[3] = 3;
    std::cout << "c3: #2" << std::endl;
    for( j = 0; j != c3.size(); ++j ){
        std::cout << c3[ j ] << " ";
    }
    std::cout << std::endl;

    //  Check for operator =
    c2 = c3;
    std::cout << "c2: #2" << std::endl;
    for( j = 0; j != c2.size(); ++j ){
        std::cout << c2[ j ] << " ";
    }
    std::cout << std::endl;

    return(0);
}
