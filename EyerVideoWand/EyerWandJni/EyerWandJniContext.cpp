#include "com_eyer_eyer_wand_editor_lib_EyerWandNative.h"
#include "EyerWand/EyerWand.hpp"
#include "EyerWand/EyerWandContext.hpp"

JNIEXPORT jlong JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1context_1init
(JNIEnv *, jclass, jint width, jint height, jint fps)
{
    Eyer::EyerWandContext * ctx = new Eyer::EyerWandContext(width, height, fps);
    return (jlong)ctx;
}

JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1context_1uninit
(JNIEnv *, jclass, jlong ctx)
{
    Eyer::EyerWandContext * wandCtx = (Eyer::EyerWandContext *)ctx;
    delete wandCtx;

    return 0;
}

JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1context_1set_1gl_1ctx
(JNIEnv *, jclass, jlong ctx, jlong thread)
{
    Eyer::EyerWandContext * wandCtx = (Eyer::EyerWandContext *)ctx;

    Eyer::EyerGLContextThread * glContextThread = (Eyer::EyerGLContextThread *)thread;

    wandCtx->SetGLCtx(glContextThread);

    return 0;
}

JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1context_1render_1frame
(JNIEnv *, jclass, jlong ctx, jdouble time)
{
    Eyer::EyerWandContext * wandCtx = (Eyer::EyerWandContext *)ctx;
    return wandCtx->RenderFrame(time);
}

JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1context_1render_1frame_1index
(JNIEnv *, jclass, jlong ctx, jint frame_index)
{
    Eyer::EyerWandContext * wandCtx = (Eyer::EyerWandContext *)ctx;
    return wandCtx->RenderFrameByIndex(frame_index);
}

JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1context_1update_1screen_1wh
(JNIEnv *, jclass, jlong ctx, jint screenW, jint screenH)
{
    Eyer::EyerWandContext * wandCtx = (Eyer::EyerWandContext *)ctx;
    return wandCtx->UpdateScreenWH(screenW, screenH);
}