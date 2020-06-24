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

    double duration = 0.0;
    videoRes->GetVideoDuration(duration);

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

JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1snapshot_1get_1wh
(JNIEnv *, jclass, jlong videoResP, jlong vec2P)
{
    Eyer::EyerWandVideoResource * videoRes = (Eyer::EyerWandVideoResource *)videoResP;
    Eyer::EyerVec2 * vec2 = (Eyer::EyerVec2 *)vec2P;

    int w = videoRes->GetW();
    int h = videoRes->GetH();

    vec2->SetX(w);
    vec2->SetY(h);

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

    Eyer::EyerAVFrame rgbaFrame;
    ret = frame.Scale(rgbaFrame, w, h, Eyer::EyerAVPixelFormat::Eyer_AV_PIX_FMT_RGBA);
    if(ret){
        return -2;
    }

    AndroidBitmapInfo info;
    int result = AndroidBitmap_getInfo(env, bitmap, &info);
    if (result != ANDROID_BITMAP_RESULT_SUCCESS) {
        return -3;
    }

    int bitmapW = info.width;
    int bitmapH = info.height;
    int stride = info.stride;
    unsigned char * buf = nullptr;
    if (ANDROID_BITMAP_RESULT_SUCCESS != AndroidBitmap_lockPixels(env, bitmap, (void **)&buf)) {
        EyerLog("lock src bitmap failed");
        return -1;
    }

    unsigned char * rgba8888 = (unsigned char *)malloc(w * h * 4);

    rgbaFrame.GetRGBAData(rgba8888);

    memcpy(buf, rgba8888, stride * bitmapH);

    AndroidBitmap_unlockPixels(env, bitmap);

    free(rgba8888);

    return 0;
}