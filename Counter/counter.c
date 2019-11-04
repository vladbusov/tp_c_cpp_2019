//
// Created by vlad on 21.10.2019.
//

//
// Created by vlad on 20.10.2019.
//
#include "counter.h"

unsigned long min(const unsigned long a, const unsigned long b) { return (a < b) ? a : b; }

void char_counter(char* chars, int* cnt_chars, const char* buffer, const unsigned long begin,
                  const unsigned long end) {
    int size_chars = (int)strlen(chars);
    for (unsigned long i = begin; i <= end; i++) {
        for (int j = 0; j < size_chars; j++) {
            if (chars[j] == buffer[i])
                cnt_chars[j] += 1;
        }
    }
}

void read_pipe(int* shared_cnt, int size, int* fd) {
    int* buf;
    int errflag;

    long l1dcls = sysconf(_SC_LEVEL1_DCACHE_LINESIZE);

    if (unlikely(l1dcls == -1))
        l1dcls = sizeof(void*);

    errflag = posix_memalign((void**)&buf, l1dcls, sizeof(int)*size);

    if (unlikely(errflag != 0))
        buf = calloc(size, sizeof(int));

    close(fd[1]);
    read(fd[0], buf, sizeof(int)*size);
    close(fd[0]);

    for (int j = 0; j < size; j++)
        shared_cnt[j] += buf[j];

    free(buf);
}

void write_pipe(char* count_buff, char* buffer, int* fd, int i, const unsigned long sizeOfChunk) {
    int* cnt = (int*)calloc(strlen(count_buff), sizeof(int));

    char_counter(count_buff, cnt, buffer, sizeOfChunk * (long)i,
                 min(sizeOfChunk * (i + 1), (int) strlen(buffer)) - 1);

    close(fd[0]);

    if (!write(fd[1], cnt, sizeof(int) * strlen(count_buff))) {
        fprintf(stderr, "Write pipe error!\n");
        return;
    }


    close(fd[1]);

    free(cnt);
}

void prl_char_counter(char* count_buff, char* buffer, int* shared_cnt) {
    long numOfProcesses = sysconf(_SC_NPROCESSORS_ONLN) * 2 + 1;

    const unsigned long sizeOfChunk = (long)strlen(buffer) / numOfProcesses + 1;


    int** fd = (int**)calloc(numOfProcesses, sizeof(int*));
    for (long i = 0; i < numOfProcesses; i++) {
        fd[i] = (int*)calloc(2, sizeof(int));
    }

    pid_t current = 0;

    for (long i = 0; i < numOfProcesses; i++) {
        pipe(fd[i]);
    }

    for (long i = 0; i < numOfProcesses; i++) {
        pid_t iter = fork();
        if (likely(iter == 0)) {
            current = i+1;
            break;
        } else if (iter == -1) {
            fprintf(stderr, "Too match processes created!\n");
            return;
        }
    }

    if (likely(current != 0)) {
        write_pipe(count_buff, buffer, fd[current - 1], current - 1, sizeOfChunk);
        exit(0);
    } else {
        wait(NULL);
    }



    for (long i = 0; i < numOfProcesses; i++) {
        read_pipe(shared_cnt, (int) strlen(count_buff), fd[i]);
        free(fd[i]);
    }

    free(fd);
}
