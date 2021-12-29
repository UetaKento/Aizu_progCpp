#include <iostream>
#include <fstream>
#include <vector>

int main(int argc, char* argv[]) {
  std::ifstream infile(argv[1]);
  std::ofstream outfile(argv[2]);
  std::vector<std::string> vecstr;
  std::string s;

  if(argc != 3) {
    std::cerr << "Error" << std::endl;
    return -1;
  }

  while (infile >> s) {
    vecstr.push_back(s);
  }
  std::sort(vecstr.begin(), vecstr.end());

  std::vector<std::string>::iterator iter = vecstr.begin();
  while (iter != vecstr.end()) {
    outfile << *iter << std::endl;
    iter++;
  }
  return 0;
}
