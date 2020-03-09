#include <stdio.h>

extern "C"
{
    #define EYER_DLLMODLE_FUNCTIONTYPE __declspec(dllexport)

    /* 测试，计算加法 */
    int     eyer_wand_csharp_test_add                       (int a, int b);

    int     eyer_wand_csharp_get_version                    (char * str_buf);



    void *  eyer_wand_csharp_builder_init                   (const char * out_path, int width, int height, int fps);
    int     eyer_wand_csharp_builder_uninit                 (void * builder);
}