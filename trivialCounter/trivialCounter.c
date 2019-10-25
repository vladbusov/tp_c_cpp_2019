//
// Created by vlad on 21.10.2019.
//

#include "trivialCounter.h"

void char_count(char* chars, char* buffer, int* sharedCnt) {
    int sizeChars = (int)strlen(chars);
    int sizeBuffer = (int)strlen(buffer);

    for (int i = 0; i < sizeBuffer; i++) {
        for (int j = 0; j < sizeChars; j++) {
            if (chars[j] == buffer[i])
                sharedCnt[j] += 1;
        }
    }
}