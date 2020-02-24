#include <stdio.h>

extern "C"
{
    /* 获取 eyer_wand 的版本号 */
    int eyer_wand_c_get_version(char * version);

    /* 测试，计算加法 */
    int eyer_wand_c_test_add(int a, int b);
}