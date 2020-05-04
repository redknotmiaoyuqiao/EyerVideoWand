#include "com_eyer_eyer_wand_editor_lib_EyerWandNative.h"

#include "EyerCrop/EyerCrop.hpp"
#include "EyerGLContext/EyerGLContext.hpp"
#include "EyerGLRenderTask/EyerGLRenderTask.hpp"

JNIEXPORT jlong JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_render_1task_1init
(JNIEnv *, jclass, jstring)
{
    Eyer::EyerGLRenderTask * renderTask = new Eyer::JuliaRenderTask();
    return (jlong)renderTask;
}


JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_render_1task_1uninit
(JNIEnv *, jclass, jlong task)
{
    Eyer::EyerGLRenderTask * renderTask = (Eyer::EyerGLRenderTask *)task;
    delete renderTask;
    return 0;
}