#include "com_eyer_eyer_wand_editor_lib_EyerWandNative.h"

#include "EyerCore/EyerCore.hpp"
#include <android/bitmap.h>

JNIEXPORT jlong JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1snapshot_1init
(JNIEnv *, jclass, jstring)
{
    return 0L;
}

JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1snapshot_1uninit
(JNIEnv *, jclass, jlong)
{
    return 0;
}

JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1snapshot_1bitmap
(JNIEnv * env, jclass, jlong, jdouble, jobject bitmap)
{
    AndroidBitmapInfo info;
    int result = AndroidBitmap_getInfo(env, bitmap, &info);
    if (result != ANDROID_BITMAP_RESULT_SUCCESS) {
        EyerLog("AndroidBitmap_getInfo failed, result: %d", result);
        return -1;
    }
    EyerLog("bitmap width: %d, height: %d, format: %d, stride: %d", info.width, info.height, info.format, info.stride);

    int w = info.width;
    int h = info.height;
    unsigned char * buf = nullptr;
    if (ANDROID_BITMAP_RESULT_SUCCESS != AndroidBitmap_lockPixels(env, bitmap, (void **)&buf)) {
        EyerLog("lock src bitmap failed");
        return -1;
    }

    for(int i=0;i<h;i++){
        EyerLog("i:%d\n",i);
        for(int j=0;j<w;j++){
            
            buf[i * w + j * 4 + 0] = 0;
            buf[i * w + j * 4 + 1] = 0;
            buf[i * w + j * 4 + 2] = 255;
            buf[i * w + j * 4 + 3] = 255;
        }
    }

    for(int i=0;i<w * h * 4;i++){
        // buf[i] = 127;
    }

    AndroidBitmap_unlockPixels(env, bitmap);
    return 0;
}