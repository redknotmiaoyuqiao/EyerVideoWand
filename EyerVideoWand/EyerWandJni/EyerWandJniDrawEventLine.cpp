#include "com_eyer_eyer_wand_editor_lib_EyerWandNative.h"

#include "EyerCrop/EyerCrop.hpp"
#include "EyerAV/EyerAV.hpp"
#include "EyerWand/EyerWand.hpp"

JNIEXPORT jlong JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1draw_1event_1line_1init
(JNIEnv *, jclass)
{
    Eyer::WandTimeLineDrawEvent_Line * line = new Eyer::WandTimeLineDrawEvent_Line();

    return (jlong)line;
}

JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1draw_1event_1line_1uninit
(JNIEnv *, jclass, jlong lineP)
{
    Eyer::WandTimeLineDrawEvent_Line * line = (Eyer::WandTimeLineDrawEvent_Line *)lineP;
    if(line != nullptr){
        delete line;
    }
    return 0;
}

JNIEXPORT jfloat JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1draw_1event_1line_1get_1start_1x
(JNIEnv *, jclass, jlong lineP)
{
    Eyer::WandTimeLineDrawEvent_Line * line = (Eyer::WandTimeLineDrawEvent_Line *)lineP;

    Eyer::EyerVec2 start;
    Eyer::EyerVec2 end;
    line->GetLine(start, end);

    return start.x();
}

JNIEXPORT jfloat JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1draw_1event_1line_1get_1start_1y
(JNIEnv *, jclass, jlong lineP)
{
    Eyer::WandTimeLineDrawEvent_Line * line = (Eyer::WandTimeLineDrawEvent_Line *)lineP;

    Eyer::EyerVec2 start;
    Eyer::EyerVec2 end;
    line->GetLine(start, end);

    return start.y();
}

JNIEXPORT jfloat JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1draw_1event_1line_1get_1end_1x
(JNIEnv *, jclass, jlong lineP)
{
    Eyer::WandTimeLineDrawEvent_Line * line = (Eyer::WandTimeLineDrawEvent_Line *)lineP;

    Eyer::EyerVec2 start;
    Eyer::EyerVec2 end;
    line->GetLine(start, end);

    return end.x();
}

JNIEXPORT jfloat JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1draw_1event_1line_1get_1end_1y
(JNIEnv *, jclass, jlong lineP)
{
    Eyer::WandTimeLineDrawEvent_Line * line = (Eyer::WandTimeLineDrawEvent_Line *)lineP;

    Eyer::EyerVec2 start;
    Eyer::EyerVec2 end;
    line->GetLine(start, end);

    return end.y();
}

JNIEXPORT jfloat JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1draw_1event_1line_1get_1color_1r
(JNIEnv *, jclass, jlong lineP)
{
    Eyer::WandTimeLineDrawEvent_Line * line = (Eyer::WandTimeLineDrawEvent_Line *)lineP;

    Eyer::EyerVec4 color;
    line->GetColor(color);

    return color.x();
}

JNIEXPORT jfloat JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1draw_1event_1line_1get_1color_1g
(JNIEnv *, jclass, jlong lineP)
{
    Eyer::WandTimeLineDrawEvent_Line * line = (Eyer::WandTimeLineDrawEvent_Line *)lineP;

    Eyer::EyerVec4 color;
    line->GetColor(color);

    return color.y();
}

JNIEXPORT jfloat JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1draw_1event_1line_1get_1color_1b
(JNIEnv *, jclass, jlong lineP)
{
    Eyer::WandTimeLineDrawEvent_Line * line = (Eyer::WandTimeLineDrawEvent_Line *)lineP;

    Eyer::EyerVec4 color;
    line->GetColor(color);

    return color.z();
}

JNIEXPORT jfloat JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1draw_1event_1line_1get_1color_1a
(JNIEnv *, jclass, jlong lineP)
{
    Eyer::WandTimeLineDrawEvent_Line * line = (Eyer::WandTimeLineDrawEvent_Line *)lineP;

    Eyer::EyerVec4 color;
    line->GetColor(color);

    return color.w();
}

JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1draw_1event_1line_1get_1strokewidth
(JNIEnv *, jclass, jlong lineP)
{
    Eyer::WandTimeLineDrawEvent_Line * line = (Eyer::WandTimeLineDrawEvent_Line *)lineP;

    return line->GetStrokeWidth();
}