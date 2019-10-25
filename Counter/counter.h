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
void char_counter(char* chars, int* cnt_chars, const char* buffer, int begin,
                  int end);
void read_pipe(int* shared_cnt, int size, int* fd);
void write_pipe(char* count_buff, char* buffer, int* fd, int pid, int i);
void prl_char_counter(char* buffer, char* count_buff, int* shared_cnt);
void print_result(int* shared_cnt, int size);

#endif // DZ2_COUNTER_H
