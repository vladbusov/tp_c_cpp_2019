//
// Created by vlad on 21.10.2019.
//

#include "trivialCounter.h"

void char_count(char* chars, char* buffer, int* shared_cnt) {
    int size_chars = (int)strlen(chars);
    int size_buffer = (int)strlen(buffer);

    for (int i = 0; i < size_buffer; i++) {
        for (int j = 0; j < size_chars; j++) {
            if (chars[j] == buffer[i])
                shared_cnt[j] += 1;
        }
    }
}