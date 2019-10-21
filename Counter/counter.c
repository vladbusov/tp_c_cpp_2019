//
// Created by vlad on 21.10.2019.
//

//
// Created by vlad on 20.10.2019.
//
#include "counter.h"

int min(int a, int b) { return (a < b) ? a : b; }

void charCounter(char* chars, int* cntChars, const char* buffer, int begin,
                 int end) {
  int sizeChars = (int)strlen(chars);

  for (int i = begin; i < end; i++) {
    for (int j = 0; j < sizeChars; j++) {
      if (chars[j] == buffer[i]) cntChars[j] += 1;
    }
  }
}

void readPipe(int* sharedCnt, int size, int* fd) {
  int buf[size];
  close(fd[1]);
  read(fd[0], buf, sizeof(buf));
  for (int j = 0; j < size; j++) {
    sharedCnt[j] += buf[j];
  }
}

void writePipe(char* countBuff, char* buffer, int* fd, int pid, int i) {
  pipe(fd);
  pid = fork();

  if (-1 == pid) { /* Error handling ... */
  } else if (0 == pid) {
    close(fd[0]);

    int* cnt = calloc(strlen(countBuff), sizeof(int));
    charCounter(countBuff, cnt, buffer, SIZE_OF_CHUNK * i,
                min(SIZE_OF_CHUNK * (i + 1), (int)strlen(buffer)));

    write(fd[1], cnt, sizeof(int) * strlen(countBuff));
    free(cnt);
    exit(0);
  }
}

void interProcessCounter(char* buffer, char* countBuff, int* sharedCnt) {
  int num;
  if (strlen(buffer) % SIZE_OF_CHUNK == 0)
    num = ((int)strlen(buffer)) / SIZE_OF_CHUNK;
  else
    num = ((int)strlen(buffer)) / SIZE_OF_CHUNK + 1;

  int** fd = (int**)calloc(num, sizeof(int*));
  for (int i = 0; i < num; i++) {
    fd[i] = (int*)calloc(2, sizeof(int));
  }

  pid_t* pid = (pid_t*)calloc(num, sizeof(pid_t));

  for (int i = 0; i < num; i++) {
    writePipe(countBuff, buffer, fd[i], pid[i], i);
  }

  for (int i = 0; i < num; i++) {
    readPipe(sharedCnt, (int)strlen(countBuff), fd[i]);
  }

  for (int i = 0; i < num; i++) {
    free(fd[i]);
  }

  free(fd);
  free(pid);
}

void printResult(int* sharedCnt, int size) {
  printf("Shared counter :\n[");

  for (int i = 0; i < size; i++) {
    printf("%d, ", sharedCnt[i]);
  }
  printf("]\n");
}