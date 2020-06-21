#include "com_eyer_eyer_wand_editor_lib_EyerWandNative.h"

#include "EyerCrop/EyerCrop.hpp"
#include "EyerAV/EyerAV.hpp"
#include "EyerWand/EyerWand.hpp"


JNIEXPORT jlong JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1draw_1event_1bitmap_1snapshot_1init
(JNIEnv *, jclass)
{
    Eyer::WandTimeLineDrawEvent_BitmapSnapshot * drawEvent = new Eyer::WandTimeLineDrawEvent_BitmapSnapshot();
    return (jlong)drawEvent;
}

JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1draw_1event_1bitmap_1snapshot_1uninit
(JNIEnv *, jclass, jlong drawEventP)
{
    Eyer::WandTimeLineDrawEvent_BitmapSnapshot * drawEvent = (Eyer::WandTimeLineDrawEvent_BitmapSnapshot *)drawEventP;
    delete drawEvent;
    return 0;
}

JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1draw_1event_1bitmap_1snapshot_1get_1src
(JNIEnv *, jclass, jlong drawEventP, jlong srcP)
{
    Eyer::WandTimeLineDrawEvent_BitmapSnapshot * drawEvent = (Eyer::WandTimeLineDrawEvent_BitmapSnapshot *)drawEventP;

    Eyer::EyerVec4 * src = (Eyer::EyerVec4 *)srcP;

    return drawEvent->GetSrc(*src);
}

JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1draw_1event_1bitmap_1snapshot_1get_1dist
(JNIEnv *, jclass, jlong drawEventP, jlong distP)
{
    Eyer::WandTimeLineDrawEvent_BitmapSnapshot * drawEvent = (Eyer::WandTimeLineDrawEvent_BitmapSnapshot *)drawEventP;

    Eyer::EyerVec4 * dist = (Eyer::EyerVec4 *)distP;

    return drawEvent->GetDist(*dist);
}

JNIEXPORT jstring JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1draw_1event_1bitmap_1snapshot_1get_1path
(JNIEnv * env, jclass, jlong drawEventP)
{
    Eyer::WandTimeLineDrawEvent_BitmapSnapshot * drawEvent = (Eyer::WandTimeLineDrawEvent_BitmapSnapshot *)drawEventP;

    Eyer::EyerString path = drawEvent->GetPath();

    return env->NewStringUTF(path.str);
}

JNIEXPORT jdouble JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1draw_1event_1bitmap_1snapshot_1get_1time
(JNIEnv *, jclass, jlong drawEventP)
{
    Eyer::WandTimeLineDrawEvent_BitmapSnapshot * drawEvent = (Eyer::WandTimeLineDrawEvent_BitmapSnapshot *)drawEventP;

    return drawEvent->GetTime();
}
