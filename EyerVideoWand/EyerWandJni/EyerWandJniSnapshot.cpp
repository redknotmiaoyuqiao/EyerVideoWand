#include "com_eyer_eyer_wand_editor_lib_EyerWandNative.h"

#include "EyerCore/EyerCore.hpp"
#include "EyerWand/EyerWand.hpp"
#include "EyerYUV/EyerYUV.hpp"
#include "JniUtil.h"
#include <android/bitmap.h>

JNIEXPORT jlong JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1snapshot_1init
(JNIEnv * env, jclass, jstring url)
{
    char * urlChar = jstringtochar(env, url);
    Eyer::EyerString urlString = urlChar;

    Eyer::EyerWandVideoResource * videoRes = new Eyer::EyerWandVideoResource();
    videoRes->SetPath(urlString);

    free(urlChar);
    return (jlong)videoRes;
}

JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1snapshot_1uninit
(JNIEnv *, jclass, jlong videoResP )
{
    Eyer::EyerWandVideoResource * videoRes = (Eyer::EyerWandVideoResource *)videoResP;
    if(videoRes != NULL){
        delete videoRes;
    }
    return 0;
}

JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1snapshot_1bitmap
(JNIEnv * env, jclass, jlong videoResP, jdouble time, jobject bitmap)
{
    Eyer::EyerWandVideoResource * videoRes = (Eyer::EyerWandVideoResource *)videoResP;

    Eyer::EyerAVFrame frame;
    int ret = videoRes->GetVideoFrame(frame, time);
    if(ret){
        return -1;
    }

    int w = frame.GetWidth();
    int h = frame.GetHeight();

    EyerLog("Frame  W: %d   H: %d\n", w, h);

    unsigned char * yuv420_y = (unsigned char *)malloc(w * h);
    unsigned char * yuv420_u = (unsigned char *)malloc(w / 2 * h / 2);
    unsigned char * yuv420_v = (unsigned char *)malloc(w / 2 * h / 2);
    unsigned char * rgba8888 = (unsigned char *)malloc(w * h * 4);

    if(yuv420_y == NULL){
        EyerLog("malloc fail!!!!\n");
        free(yuv420_y);
        free(yuv420_u);
        free(yuv420_v);
        free(rgba8888);
        return -1;
    }
    if(yuv420_u == NULL){
        EyerLog("malloc fail!!!!\n");
        free(yuv420_y);
        free(yuv420_u);
        free(yuv420_v);
        free(rgba8888);
        return -1;
    }
    if(yuv420_v == NULL){
        EyerLog("malloc fail!!!!\n");
        free(yuv420_y);
        free(yuv420_u);
        free(yuv420_v);
        free(rgba8888);
        return -1;
    }
    if(rgba8888 == NULL){
        EyerLog("malloc fail!!!!\n");
        free(yuv420_y);
        free(yuv420_u);
        free(yuv420_v);
        free(rgba8888);
        return -1;
    }

    frame.GetYData(yuv420_y);
    frame.GetUData(yuv420_u);
    frame.GetVData(yuv420_v);

    Eyer::EyerYUV yuvUtil;
    yuvUtil.I420_TO_RGBA(w, h, yuv420_y, yuv420_u, yuv420_v, rgba8888);

    AndroidBitmapInfo info;
    int result = AndroidBitmap_getInfo(env, bitmap, &info);
    if (result != ANDROID_BITMAP_RESULT_SUCCESS) {
        EyerLog("AndroidBitmap_getInfo failed, result: %d", result);

        free(yuv420_y);
        free(yuv420_u);
        free(yuv420_v);
        free(rgba8888);
        return -1;
    }
    EyerLog("bitmap width: %d, height: %d, format: %d, stride: %d", info.width, info.height, info.format, info.stride);

    int bitmapW = info.width;
    int bitmapH = info.height;
    int stride = info.stride;
    unsigned char * buf = nullptr;
    if (ANDROID_BITMAP_RESULT_SUCCESS != AndroidBitmap_lockPixels(env, bitmap, (void **)&buf)) {
        EyerLog("lock src bitmap failed");

        free(yuv420_y);
        free(yuv420_u);
        free(yuv420_v);
        free(rgba8888);
        return -1;
    }

    memcpy(buf, rgba8888, stride * bitmapH);

    AndroidBitmap_unlockPixels(env, bitmap);


    free(yuv420_y);
    free(yuv420_u);
    free(yuv420_v);
    free(rgba8888);
    return 0;
}