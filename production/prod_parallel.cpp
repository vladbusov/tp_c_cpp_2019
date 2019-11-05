#include <cstring>
#include <fstream>
#include <iostream>

#define FILESIZE 104857600
extern "C" {
#include "../Counter/counter.h"
}

using std::exception;
using std::ifstream;
using std::ofstream;
using std::string;

string readFile(const string& fileName) {
  ifstream f(fileName);
  f.seekg(0, std::ios::end);
  size_t size = f.tellg();
  string s(size, ' ');
  f.seekg(0);
  f.read(&s[0], size);
  return s;
}

int main(int argc, char** argv) {
  if (argc < 2) throw exception();

  string buffStr = readFile(argv[1]);
  char* buffChar = new char[buffStr.size() + 1];
  snprintf(buffChar, buffStr.size() + 1, "%s", buffStr.c_str());

  char countBuff[] = "Vlad Busov";

  int* result = new int[strlen(countBuff)];
  memset(result, 0, sizeof(int) * strlen(countBuff));

  prl_char_counter(countBuff, buffChar, result);

  delete[] buffChar;
  delete[] result;
  return 0;
}
