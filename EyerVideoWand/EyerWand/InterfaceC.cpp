#include "InterfaceC.h"
#include "EyerWand.hpp"

#include <string.h>
#include <stdlib.h>

int             eyer_wand_c_get_version         (char * version)
{
    int version_len = strlen(EYER_WAND_VERSION);
    memcpy(version, EYER_WAND_VERSION, version_len);
    return 0;
}

int             eyer_wand_c_test_add            (int a, int b)
{
    return a + b;
}

void *          eyer_wand_c_builder_init          (const char * out_path, int width, int height, int fps)
{
    Eyer::EyerWandBuilder * builder = new Eyer::EyerWandBuilder(out_path);
    builder->SetVideoWH(1280, 720);
    builder->SetVideoFPS(fps);

    return (void *)builder;
}

int             eyer_wand_c_builder_uninit        (void * builder)
{
    Eyer::EyerWandBuilder * builder_p = (Eyer::EyerWandBuilder * )builder;
    if(builder_p != NULL){
        delete builder_p;
    }
    return 0;
}

int             eyer_wand_c_builder_add_video_track   (void * _builder, void * _video_track)
{
    Eyer::EyerWandBuilder * builder = (Eyer::EyerWandBuilder * )_builder;
    Eyer::EyerVideoTrack * videoTrack = (Eyer::EyerVideoTrack *)_video_track;

    return builder->AddVideoTrack(*videoTrack);
}

void *          eyer_wand_c_video_track_init      ()
{
    Eyer::EyerVideoTrack * videoTrack = new Eyer::EyerVideoTrack();

    return (void *)videoTrack;
}

int             eyer_wand_c_video_track_uninit    (void * video_track)
{
    Eyer::EyerVideoTrack * videoTrack = (Eyer::EyerVideoTrack *)video_track;
    if(videoTrack != NULL){
        delete videoTrack;
    }
    return 0;
}