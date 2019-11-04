#include <cstring>
#include <gtest/gtest.h>
#include <iostream>

extern "C" {
#include "../Counter/counter.h"
#include "../trivialCounter/trivialCounter.h"
}

class TestSerialization : public ::testing::Test {
 public:
    TestSerialization() = default;
    ~TestSerialization() override = default;
};



TEST_F(TestSerialization, bufferTest) {
    char buffer[] = "5dl_@qCW cGl{Ia0jBS$'-JF"
                    "'#-|;%Bji0eF=*}=*G,',)Rv"
                    "'6m4`5;}CT:bv&NB(0_L/9Vp"
                    "/vw'9acAq_m<xFIs@a]lr0AT"
                    "P_3A!Up0MiR\"LQCY23uFs@;"
                    "5$5#2_^\"KZ5l[j^'TcsVKG6"
                    "W}7ym7nEbQu%aZ=941,#DiI$"
                    "lPK=2^t&]G!L^+-]w%bZ_;st"
                    "f;w,&]1s/vL[V\\aO%|{ *+w"
                    "vB$t@> e7=u.6\"Z$$oH9L.-"
                    "TgJT*Da)<&G3`\"MG9'Xb=ZX"
                    "^I@3uNZeQ&<[e9 #?aP;c:b9"
                    "(_Bsz'/yZjQWddIWr iOLfL`"
                    "OjLtolT4Mv)c:8xt>Lh$LMuZ"
                    "M{+y}rvNx^DjLy 5-C5Gu/X5"
                    "s\\D$PY6rIZ}00Wrp`o`H\"K"
                    "Dr;lyFLJs[(:zr/2fX(!h8rv"
                    "+Tg'8&R\\4nK063Z++|_'po9";

    char countBuff[] = "Vlad Busov";

    int* result1 = new int[strlen(countBuff)];
    memset(result1, 0, sizeof(int) * strlen(countBuff));
    int* result2 = new int[strlen(countBuff)];
    memset(result2, 0, sizeof(int) * strlen(countBuff));

    char_count(countBuff, buffer, result1);
    prl_char_counter(countBuff, buffer, result2);


    EXPECT_EQ(0, std::memcmp(result1, result2, strlen(countBuff) * sizeof(int)));

    delete[] result1;
    delete[] result2;
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
