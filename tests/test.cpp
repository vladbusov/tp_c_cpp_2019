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
    char buffer[] = "5dl_@qCW cGl{Ia0jBS$'-JF'#-|;%Bji0eF=*}=*G,',)RvL'6m4`5;}CT:bv&NB(0_L/9Vp_^8hL06SF@$BU?B4"
                    "/vw'9acAq_m<xFIs@a]lr0ATP_3A!Up0MiR\"LQCY23uFs@;5$5#2_^\"KZ5l[j^'TcsVKG6&sI8<XrqmvB,D#&GN"
                    "W}7ym7nEbQu%aZ=941,#DiI$lPK=2^t&]G!L^+-]w%bZ_;stf;w,&]1s/vL[V\\aO%|{ *+w#0u]o2l!4)5AJrlY#"
                    "vB$t@> e7=u.6\"Z$$oH9L.-TgJT*Da)<&G3`\"MG9'Xb=ZX\\^I@3uNZeQ&<[e9 #?aP;c:b9A<{x3UV-;2AL`{4"
                    "(_Bsz'/yZjQWddIWr iOLfL`OjLtolT4Mv)c:8xt>Lh$LMuZM{+y}rvNx^DjLy 5-C5Gu/X5uBSDoe:Xb`maTe1h`"
                    "s\\D$PY6rIZ}00Wrp`o`H\"KDr;lyFLJs[(:zr/2fX(!h8rv+Tg'8&R\\4nK063Z++|_'po9rIA/4s#F:q0B,6t$J"
                    "hWKtH $rAMBPPhkD4/jJ?n1@Z'psrh9vBd)&dG4AuV-a[xA+C-pc|#?XDKgRP\"e.\"*4\"kI]b;j`2e#>D10CIMb"
                    "DQX`>#?=?+}k,<+QgUt2$sOv?oXU3!yqlSSFqrcL:|9F;E3$6*Q;9\"MX.AI[B^OJ3>p&Mpl#n(I+g]J}#{:<9#0a"
                    "Ku4;}xa\"WG\"t^V23ZBu:76=j@%l$^uP+) aBx^Ek'aa!9s4/Q+d$A#n{(]<#n(Hw(+V#%{*F^lG3{\\]igCmE`x"
                    "b{dlC^tk-.cjwLI\"-E6jJ) k'=W8bO!Ff!NE_E2(S1sf^X$k ;qd^rQ!1+SstnU\\o%#jdPsSa$;[vZc2uVvoJdq"
                    ">7 \\l[TH@gY3yK]_>U& [AQ9Tt6k?wm]0);}eoaAr=nn$Ni\\?p\\6M0i$&!o_5x>E$s^% \\`syQ}9;huttS,D}";

    char countBuff[] = "Vlad Busov";

    int* result1 = new int[strlen(countBuff)];
    memset(result1, 0, sizeof(int) * strlen(countBuff));
    int* result2 = new int[strlen(countBuff)];
    memset(result2, 0, sizeof(int) * strlen(countBuff));

    char_count(countBuff, buffer, result1);
    prl_char_counter(countBuff, buffer, result2);


    EXPECT_EQ(0,std::memcmp(result1, result2, strlen(countBuff) * sizeof(int)));

    delete[] result1;
    delete[] result2;
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}