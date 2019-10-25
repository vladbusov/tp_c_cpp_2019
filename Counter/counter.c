//
// Created by vlad on 21.10.2019.
//

//
// Created by vlad on 20.10.2019.
//
#include "counter.h"

int min(int a, int b) { return (a < b) ? a : b; }

void char_counter(char* chars, int* cnt_chars, const char* buffer, int begin,
                  int end)
{
    int size_chars = (int)strlen(chars);

    for (int i = begin; i < end; i++) {
        for (int j = 0; j < size_chars; j++) {
            if (chars[j] == buffer[i])
                cnt_chars[j] += 1;
        }
    }
}

void read_pipe(int* shared_cnt, int size, int* fd)
{
    int buf[size];
    close(fd[1]);
    read(fd[0], buf, sizeof(buf));
    for (int j = 0; j < size; j++) {
        shared_cnt[j] += buf[j];
    }
}

void write_pipe(char* count_buff, char* buffer, int* fd, int pid, int i)
{
    pipe(fd);
    pid = fork();

    if (-1 == pid) { /* Error handling ... */
    } else if (0 == pid) {
        close(fd[0]);

        int* cnt = calloc(strlen(count_buff), sizeof(int));
        char_counter(count_buff, cnt, buffer, SIZE_OF_CHUNK * i,
                     min(SIZE_OF_CHUNK * (i + 1), (int) strlen(buffer)));

        write(fd[1], cnt, sizeof(int) * strlen(count_buff));
        free(cnt);
        exit(0);
    }
}

void prl_char_counter(char* buffer, char* count_buff, int* shared_cnt)
{
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
        write_pipe(count_buff, buffer, fd[i], pid[i], i);
    }

    for (int i = 0; i < num; i++) {
        read_pipe(shared_cnt, (int) strlen(count_buff), fd[i]);
    }

    for (int i = 0; i < num; i++) {
        free(fd[i]);
    }

    free(fd);
    free(pid);
}

void print_result(int* shared_cnt, int size)
{
    printf("Shared counter :\n[");

    for (int i = 0; i < size; i++) {
        printf("%d, ", shared_cnt[i]);
    }
    printf("]\n");
}