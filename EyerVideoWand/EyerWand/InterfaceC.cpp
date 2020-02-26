#include "InterfaceC.h"
#include "EyerWand.hpp"

int eyer_wand_c_get_version(char * version)
{
    int version_len = strlen(EYER_WAND_VERSION);
    memcpy(version, EYER_WAND_VERSION, version_len);
    return 0;
}

int eyer_wand_c_test_add(int a, int b)
{
    return a + b;
}