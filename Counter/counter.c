//
// Created by vlad on 21.10.2019.
//

//
// Created by vlad on 20.10.2019.
//
#include <wait.h>
#include "counter.h"

int min(int a, int b) { return (a < b) ? a : b; }

void char_counter(char* chars, int* cnt_chars, const char* buffer, int begin,
                  int end)
{
    int size_chars = (int)strlen(chars);
    int endr = 0;

    for (int i = begin; i <= end; i++) {
        for (int j = 0; j < size_chars; j++) {
            if (chars[j] == buffer[i])
                cnt_chars[j] += 1;
        }
        endr = i;
    }
}

void read_pipe(int* shared_cnt, int size, int* fd)
{
    int* buf = calloc(size, sizeof(int));

    close(fd[1]);
    read(fd[0], buf, sizeof(int)*size);
    close(fd[0]);

    for (int j = 0; j < size; j++) {
        shared_cnt[j] += buf[j];
    }
    free(buf);

}

void write_pipe(char* count_buff, char* buffer, int* fd, int i)
{

    int* cnt = calloc(strlen(count_buff), sizeof(int));

    char_counter(count_buff, cnt, buffer, SIZE_OF_CHUNK * i,
                 min(SIZE_OF_CHUNK * (i + 1), (int) strlen(buffer)  ) -1);

    close(fd[0]);
    int err = write(fd[1], cnt, sizeof(int) * strlen(count_buff));
    close(fd[1]);

    free(cnt);
}

void prl_char_counter(char* buffer, char* count_buff, int* shared_cnt)
{
    unsigned long num;
    if (strlen(buffer) % SIZE_OF_CHUNK == 0)
        num = ((unsigned long)strlen(buffer)) / SIZE_OF_CHUNK;
    else
        num = ((unsigned long)strlen(buffer)) / SIZE_OF_CHUNK + 1;

    int** fd = (int**)calloc(num, sizeof(int*));
    for (int i = 0; i < num; i++) {
        fd[i] = (int*)calloc(2, sizeof(int));
    }

    pid_t current = 0;
    pid_t offset = getpid();

    for (int i = 0; i < num; i++) {
        pipe(fd[i]);
    }

    for (int i = 0; i < num; i++) {
        pid_t iter = fork();
        if (iter == 0)
        {
            // дочерний - создался и вышел
            current = i+1;
            break;
        }
        else if (iter == -1)
        {
            fprintf(stderr, "Too match processes created!");
            return;
        }
    }

    if (current != 0) {
        write_pipe(count_buff, buffer, fd[current - 1], current - 1);
        exit(0);
    } else {
        wait(NULL);
    }



    for (int i = 0; i < num; i++) {
        read_pipe(shared_cnt, (int) strlen(count_buff), fd[i]);
    }

    for (int i = 0; i < num; i++) {
        free(fd[i]);
    }

    free(fd);
}

void print_result(int* shared_cnt, int size)
{
    printf("Shared counter :\n[");

    for (int i = 0; i < size; i++) {
        printf("%d, ", shared_cnt[i]);
    }
    printf("]\n");
}