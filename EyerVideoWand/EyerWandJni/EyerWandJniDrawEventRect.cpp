#include "com_eyer_eyer_wand_editor_lib_EyerWandNative.h"

#include "EyerCrop/EyerCrop.hpp"
#include "EyerAV/EyerAV.hpp"
#include "EyerWand/EyerWandContext.hpp"

JNIEXPORT jlong JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1draw_1event_1rect_1init
(JNIEnv *, jclass)
{
    Eyer::WandTimeLineDrawEvent_Rect * rect = new Eyer::WandTimeLineDrawEvent_Rect();

    return (jlong)rect;
}

JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1draw_1event_1rect_1uninit
(JNIEnv *, jclass, jlong rectP)
{
    Eyer::WandTimeLineDrawEvent_Rect * rect = (Eyer::WandTimeLineDrawEvent_Rect *)rectP;

    if(rect != nullptr){
        delete rect;
        rect = nullptr;
    }

    return 0;
}


JNIEXPORT jfloat JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1draw_1event_1rect_1get_1start_1x
(JNIEnv *, jclass, jlong rectP)
{
    Eyer::WandTimeLineDrawEvent_Rect * rect = (Eyer::WandTimeLineDrawEvent_Rect *)rectP;

    Eyer::EyerVec2 start;
    Eyer::EyerVec2 end;
    rect->GetRect(start, end);

    return start.x();
}

JNIEXPORT jfloat JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1draw_1event_1rect_1get_1start_1y
(JNIEnv *, jclass, jlong rectP)
{
    Eyer::WandTimeLineDrawEvent_Rect * rect = (Eyer::WandTimeLineDrawEvent_Rect *)rectP;

    Eyer::EyerVec2 start;
    Eyer::EyerVec2 end;
    rect->GetRect(start, end);

    return start.y();
}

JNIEXPORT jfloat JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1draw_1event_1rect_1get_1end_1x
(JNIEnv *, jclass, jlong rectP)
{
    Eyer::WandTimeLineDrawEvent_Rect * rect = (Eyer::WandTimeLineDrawEvent_Rect *)rectP;

    Eyer::EyerVec2 start;
    Eyer::EyerVec2 end;
    rect->GetRect(start, end);

    return end.x();
}

JNIEXPORT jfloat JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1draw_1event_1rect_1get_1end_1y
(JNIEnv *, jclass, jlong rectP)
{
    Eyer::WandTimeLineDrawEvent_Rect * rect = (Eyer::WandTimeLineDrawEvent_Rect *)rectP;

    Eyer::EyerVec2 start;
    Eyer::EyerVec2 end;
    rect->GetRect(start, end);

    return end.y();
}

JNIEXPORT jfloat JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1draw_1event_1rect_1get_1color_1r
(JNIEnv *, jclass, jlong rectP)
{
    Eyer::WandTimeLineDrawEvent_Rect * rect = (Eyer::WandTimeLineDrawEvent_Rect *)rectP;

    Eyer::EyerVec4 color;
    rect->GetColor(color);

    return color.x();
}

JNIEXPORT jfloat JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1draw_1event_1rect_1get_1color_1g
(JNIEnv *, jclass, jlong rectP)
{
    Eyer::WandTimeLineDrawEvent_Rect * rect = (Eyer::WandTimeLineDrawEvent_Rect *)rectP;

    Eyer::EyerVec4 color;
    rect->GetColor(color);

    return color.y();
}

JNIEXPORT jfloat JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1draw_1event_1rect_1get_1color_1b
(JNIEnv *, jclass, jlong rectP)
{
    Eyer::WandTimeLineDrawEvent_Rect * rect = (Eyer::WandTimeLineDrawEvent_Rect *)rectP;

    Eyer::EyerVec4 color;
    rect->GetColor(color);

    return color.z();
}

JNIEXPORT jfloat JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1draw_1event_1rect_1get_1color_1a
(JNIEnv *, jclass, jlong rectP)
{
    Eyer::WandTimeLineDrawEvent_Rect * rect = (Eyer::WandTimeLineDrawEvent_Rect *)rectP;

    Eyer::EyerVec4 color;
    rect->GetColor(color);

    return color.w();
}