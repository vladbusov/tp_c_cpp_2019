#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>

#define FILESIZE 104857600

using std::exception;
using std::ifstream;
using std::ofstream;
using std::string;

void makeTestFile(const string& fileName) {
  ofstream testFile(fileName);

  unsigned int seed = 0;
  srand(time(NULL));

  for (int i = 0; i < FILESIZE; i++) {
    char ch = (rand_r(&seed) % 94) + 32;
    testFile << ch;
  }
  testFile.close();
}

int main(int argc, char** argv) {
  if (argc < 2) throw exception();
  makeTestFile(argv[1]);
  return 0;
}
