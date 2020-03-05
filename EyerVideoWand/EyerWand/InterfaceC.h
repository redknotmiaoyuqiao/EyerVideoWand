#include <stdio.h>

extern "C"
{
    /* 获取 eyer_wand 的版本号 */
    int             eyer_wand_c_get_version             (char * version);

    /* 测试，计算加法 */
    int             eyer_wand_c_test_add                (int a, int b);

    void *          eyer_wand_c_builder_init              (const char * out_path, int width, int height, int fps);
    int             eyer_wand_c_builder_uninit            (void * builder);
    int             eyer_wand_c_builder_add_video_track   (void * builder, void * video_track);

    void *          eyer_wand_c_video_track_init          ();
    int             eyer_wand_c_video_track_uninit        (void * video_track);
}