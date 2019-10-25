//
// Created by vlad on 21.10.2019.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef DZ2_COUNTER_H
#define DZ2_COUNTER_H

//
// Created by vlad on 20.10.2019.
//

#define SIZE_OF_CHUNK 1000000

int min(int a, int b);
void char_counter(char* chars, int* cntChars, const char* buffer, int begin,
                  int end);
void read_pipe(int* sharedCnt, int size, int* fd);
void write_pipe(char* countBuff, char* buffer, int* fd, int pid, int i);
void prl_char_counter(char* buffer, char* countBuff, int* sharedCnt);
void print_result(int* sharedCnt, int size);

#endif // DZ2_COUNTER_H
