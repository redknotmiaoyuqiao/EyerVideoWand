#include "com_eyer_eyer_wand_editor_lib_EyerWandNative.h"

#include "EyerCrop/EyerCrop.hpp"
#include "EyerAV/EyerAV.hpp"
#include "EyerWand/EyerWand.hpp"

JNIEXPORT jlong JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1draw_1event_1bitmap_1init
(JNIEnv *, jclass)
{
    Eyer::WandTimeLineDrawEvent_Bitmap * drawEvent = new Eyer::WandTimeLineDrawEvent_Bitmap();
    return (jlong)drawEvent;
}

JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1draw_1event_1bitmap_1uninit
(JNIEnv *, jclass, jlong drawEventP)
{
    Eyer::WandTimeLineDrawEvent_Bitmap * drawEvent = (Eyer::WandTimeLineDrawEvent_Bitmap *)drawEventP;
    delete drawEvent;
    return 0;
}

JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1draw_1event_1bitmap_1get_1src
(JNIEnv *, jclass, jlong drawEventP, jlong srcP)
{
    Eyer::WandTimeLineDrawEvent_Bitmap * drawEvent = (Eyer::WandTimeLineDrawEvent_Bitmap *)drawEventP;

    Eyer::EyerVec4 * src = (Eyer::EyerVec4 *)srcP;

    return drawEvent->GetSrc(*src);
}

JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1draw_1event_1bitmap_1get_1dist
(JNIEnv *, jclass, jlong drawEventP, jlong distP)
{
    Eyer::WandTimeLineDrawEvent_Bitmap * drawEvent = (Eyer::WandTimeLineDrawEvent_Bitmap *)drawEventP;

    Eyer::EyerVec4 * dist = (Eyer::EyerVec4 *)distP;

    return drawEvent->GetDist(*dist);
}