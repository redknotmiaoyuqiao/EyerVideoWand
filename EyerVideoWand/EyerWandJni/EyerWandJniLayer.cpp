#include "com_eyer_eyer_wand_editor_lib_EyerWandNative.h"

#include "EyerGLContext/EyerGLContext.hpp"
#include "EyerGL/EyerGLRenderTask/EyerGLRenderTask.hpp"
#include "EyerWand/EyerWandContext.hpp"


JNIEXPORT jlong JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1layer_1init
(JNIEnv *, jclass)
{
    Eyer::EyerVideoLayer * layer = new Eyer::EyerVideoLayer();
    return (jlong)layer;
}

JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1layer_1uninit
(JNIEnv *, jclass, jlong layerP)
{
    Eyer::EyerVideoLayer * layer = (Eyer::EyerVideoLayer *)layerP;
    delete layer;
    return 0;
}