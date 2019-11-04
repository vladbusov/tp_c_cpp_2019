#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

#ifndef COUNTER_COUNTER_H_
#define COUNTER_COUNTER_H_

#define unlikely(expr) __builtin_expect(!!(expr), 0)
#define likely(expr) __builtin_expect(!!(expr), 1)

unsigned long min(const unsigned long a, const unsigned long b);
void char_counter(char* chars, int* cnt_chars, const char* buffer, const unsigned long begin,
                  const unsigned long end);
void read_pipe(int* shared_cnt, int size, int* fd);
void write_pipe(char* count_buff, char* buffer, int* fd, int i, const unsigned long sizeOfChunk);
void prl_char_counter(char* count_buff, char* buffer, int* shared_cnt);

#endif  // COUNTER_COUNTER_H_
