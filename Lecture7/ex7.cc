#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cctype>
#include <iomanip>
#include <iterator>
#include <map>
#include <fstream>

using namespace std;

//find_if関数で使用する判別関数
bool not_space(char c){
    return(!isspace(c));
}
bool space(char c){
    return(isspace(c));
}

//1行を単語に区切る関数split
vector<string> split(string s){
    vector<string> words;

    for(string::size_type i = 0; i != s.size(); ++i){
        if(s[i] == '.' || s[i] == ',' || s[i] == '\"' || s[i] == '(' || s[i] == ')' || s[i] == '?'){
            s[i] = ' ';
        }
        s[i] = tolower(s[i]);
        //cout << s[i];
    }
    cout << endl;


    string::iterator i = s.begin(), j; //iで単語の先頭のイテレータを示す。jで単語の後ろのスペースのイテレータを示す

    while(j != s.end()){
        string word;

        i = find_if(i, s.end(), not_space);
        j = find_if(i, s.end(), space);

        copy(i, j, back_inserter(word));
        words.push_back(word);

        i = j;
    }

    return words;
}

int main(){
    map< string, vector<int> > counters; //mapで単語と行番号の格納

    string search_word, filename; //検索単語、ファイルの名前
    string s; //ファイルの文字読み込み用
    vector<string> words; //1行を単語に分けて格納する

    int count = 0; //行数の格納

    //検索単語、ファイルの名前の順に入力
    cin >> search_word >> filename;
    ifstream ifs(filename);
    if (!ifs) {
        cout << "ファイルオープンに失敗" << endl;
        exit(1);
    }

    //1行ずつ読み込み、単語に分けて行数を保存
    while(getline(cin, s)){
        words = split(s); //単語を分ける

        //行数を保存
        for(int i = 0; i < words.size(); i++){
            counters[words[i]].push_back(count);
        }

        ++count; //行数を増やす
    }

    //検索したい単語の出力
    cout << search_word << " is appeared at ";
    for(int i = 1; i < counters[search_word].size(); ++i){
        cout << counters[search_word][i] << " ";
    }
    cout << endl;

    return 0;
}
