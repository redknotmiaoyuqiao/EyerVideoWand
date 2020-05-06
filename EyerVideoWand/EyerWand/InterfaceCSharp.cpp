#include "InterfaceCSharp.h"
#include "InterfaceC.h"

#include "EyerCore/EyerCore.hpp"

int eyer_wand_csharp_test_add(int a, int b)
{
    return eyer_wand_c_test_add(a, b);
}

int     eyer_wand_csharp_get_version                    (char * str_buf)
{
    return eyer_wand_c_get_version(str_buf);
}

void *  eyer_wand_csharp_builder_init                   (const char * out_path, int width, int height, int fps)
{
    return eyer_wand_c_builder_init(out_path, width, height, fps);
}

int     eyer_wand_csharp_builder_uninit                 (void * builder)
{
    return eyer_wand_c_builder_uninit(builder);
}