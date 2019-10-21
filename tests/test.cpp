#include <gtest/gtest.h>
#include <stdio.h>
#include <cstring>
#include <ctime>
#include <iostream>

extern "C" {
#include "../Counter/counter.h"
#include "../trivialCounter/trivialCounter.h"
}

#define FILESIZE 104857600

class TestSerialization : public ::testing::Test {
 public:
  TestSerialization() {
    FILE* mf = fopen("test.txt", "w");

    srand(time(NULL));

    for (int i = 0; i < FILESIZE; i++) {
      char ch = rand() % 255;
      fputc(ch, mf);
    }

    fclose(mf);
  }
  ~TestSerialization() { /* free protected members here */
  }
  void SetUp() { /* called before every test */
  }
  void TearDown() { /* called after every test */
  }

 protected:
  /* none yet */
};

TEST_F(TestSerialization, testRealization) {
  FILE* mf = fopen("test.txt", "r");
  char* buffer = new char[FILESIZE];
  fgets(buffer, FILESIZE, mf);
  fclose(mf);

  char countBuff[] = "Vlad Busov";

  int* result1 = new int[strlen(countBuff)];
  memset(result1, 0, sizeof(int) * strlen(countBuff));
  int* result2 = new int[strlen(countBuff)];
  memset(result2, 0, sizeof(int) * strlen(countBuff));

  charCount(countBuff, buffer, result1);
  interProcessCounter(buffer, countBuff, result2);

  EXPECT_TRUE(0 ==
              std::memcmp(result1, result2, strlen(countBuff) * sizeof(int)));

  delete[] buffer;
  delete[] result1;
  delete[] result2;
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}