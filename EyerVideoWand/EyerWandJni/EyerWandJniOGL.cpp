#include "com_eyer_eyer_wand_editor_lib_EyerWandNative.h"

#include "EyerGLContext/EyerGLContext.hpp"
#include <android/native_window_jni.h>

JNIEXPORT jlong JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_ogl_1create_1thread
(JNIEnv * env, jclass, jobject surface)
{
    ANativeWindow * nativeWindow = ANativeWindow_fromSurface(env, surface);

    Eyer::EyerGLContextThread * glContextThread = new Eyer::EyerGLContextThread(nativeWindow);
    glContextThread->Start();
    return (jlong)glContextThread;
}

JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_ogl_1stop_1thread
(JNIEnv *, jclass, jlong thread)
{
    Eyer::EyerGLContextThread * glContextThread = (Eyer::EyerGLContextThread *)thread;
    glContextThread->Stop();
    delete glContextThread;
    
    return 0;
}

JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_ogl_1set_1wh
(JNIEnv *, jclass, jlong thread, jint w, jint h)
{
    Eyer::EyerGLContextThread * glContextThread = (Eyer::EyerGLContextThread *)thread;
    return glContextThread->SetWH(w, h);
}