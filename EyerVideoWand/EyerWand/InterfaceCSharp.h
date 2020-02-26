#include <stdio.h>

extern "C"
{
    #define EYER_DLLMODLE_FUNCTIONTYPE __declspec(dllexport)

    /* 测试，计算加法 */
    int eyer_wand_csharp_test_add(int a, int b);
}