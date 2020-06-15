#include "com_eyer_eyer_wand_editor_lib_EyerWandNative.h"

#include "EyerCrop/EyerCrop.hpp"
#include "EyerAV/EyerAV.hpp"
#include "EyerWand/EyerWandContext.hpp"


/**
 * Vec2
 */
JNIEXPORT jlong JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1vec2_1init
(JNIEnv *, jclass)
{
    Eyer::EyerVec2 * vec2 = new Eyer::EyerVec2();
    return (jlong)vec2;
}

JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1vec2_1uninit
(JNIEnv *, jclass, jlong vec2P)
{
    Eyer::EyerVec2 * vec2 = (Eyer::EyerVec2 *)vec2P;
    delete vec2;
    return 0;
}

JNIEXPORT jfloat JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1vec2_1get_1x
(JNIEnv *, jclass, jlong vec2P)
{
    Eyer::EyerVec2 * vec2 = (Eyer::EyerVec2 *)vec2P;
    return vec2->x();
}

JNIEXPORT jfloat JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1vec2_1get_1y
(JNIEnv *, jclass, jlong vec2P)
{
    Eyer::EyerVec2 * vec2 = (Eyer::EyerVec2 *)vec2P;
    return vec2->y();
}



/**
 * Vec3
 */
JNIEXPORT jlong JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1vec3_1init
(JNIEnv *, jclass)
{
    Eyer::EyerVec3 * vec3 = new Eyer::EyerVec3();
    return (jlong)vec3;
}

JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1vec3_1uninit
(JNIEnv *, jclass, jlong vec3P)
{
    Eyer::EyerVec3 * vec3 = (Eyer::EyerVec3 *)vec3P;
    delete vec3;
    return 0;
}

JNIEXPORT jfloat JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1vec3_1get_1x
(JNIEnv *, jclass, jlong vec3P)
{
    Eyer::EyerVec3 * vec3 = (Eyer::EyerVec3 *)vec3P;
    return vec3->x();
}

JNIEXPORT jfloat JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1vec3_1get_1y
(JNIEnv *, jclass, jlong vec3P)
{
    Eyer::EyerVec3 * vec3 = (Eyer::EyerVec3 *)vec3P;
    return vec3->y();
}

JNIEXPORT jfloat JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1vec3_1get_1z
(JNIEnv *, jclass, jlong vec3P)
{
    Eyer::EyerVec3 * vec3 = (Eyer::EyerVec3 *)vec3P;
    return vec3->z();
}





/**
 * Vec4
 */
JNIEXPORT jlong JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1vec4_1init
(JNIEnv *, jclass)
{
    Eyer::EyerVec4 * vec4 = new Eyer::EyerVec4();
    return (jlong)vec4;
}

JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1vec4_1uninit
(JNIEnv *, jclass, jlong vec4P)
{
    Eyer::EyerVec4 * vec4 = (Eyer::EyerVec4 *)vec4P;
    delete vec4;
    return 0;
}

JNIEXPORT jfloat JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1vec4_1get_1x
(JNIEnv *, jclass, jlong vec4P)
{
    Eyer::EyerVec4 * vec4 = (Eyer::EyerVec4 *)vec4P;
    return vec4->x();
}

JNIEXPORT jfloat JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1vec4_1get_1y
(JNIEnv *, jclass, jlong vec4P)
{
    Eyer::EyerVec4 * vec4 = (Eyer::EyerVec4 *)vec4P;
    return vec4->y();
}

JNIEXPORT jfloat JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1vec4_1get_1z
(JNIEnv *, jclass, jlong vec4P)
{
    Eyer::EyerVec4 * vec4 = (Eyer::EyerVec4 *)vec4P;
    return vec4->z();
}

JNIEXPORT jfloat JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1vec4_1get_1w
(JNIEnv *, jclass, jlong vec4P)
{
    Eyer::EyerVec4 * vec4 = (Eyer::EyerVec4 *)vec4P;
    return vec4->w();
}