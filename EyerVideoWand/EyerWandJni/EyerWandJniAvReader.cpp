#include "com_eyer_eyer_wand_editor_lib_EyerWandNative.h"

#include "EyerCrop/EyerCrop.hpp"
#include "EyerAV/EyerAV.hpp"
#include "EyerWand/EyerWandContext.hpp"

#include "JniUtil.h"

char* jstringtochar( JNIEnv *env, jstring jstr );

JNIEXPORT jlong JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_avreader_1init
(JNIEnv * env, jclass, jstring url)
{
    char * urlChar = jstringtochar(env, url);

    Eyer::EyerString urlString = urlChar;

    // EyerLog("AvReader Init Url: %s\n", urlString.str);

    Eyer::EyerAVReader * avReader = new Eyer::EyerAVReader(urlString);


    free(urlChar);
    return (jlong)avReader;
}

JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_avreader_1uninit
(JNIEnv *, jclass, jlong reader)
{
    Eyer::EyerAVReader * avReader = (Eyer::EyerAVReader *)reader;

    delete avReader;

    return 0;
}

JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_avreader_1open
(JNIEnv *, jclass, jlong reader)
{
    Eyer::EyerAVReader * avReader = (Eyer::EyerAVReader *)reader;

    return avReader->Open();
}

JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_avreader_1close
(JNIEnv *, jclass, jlong reader)
{
    Eyer::EyerAVReader * avReader = (Eyer::EyerAVReader *)reader;

    return avReader->Close();
}

JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_avreader_1print_1info
(JNIEnv *, jclass, jlong reader)
{
    Eyer::EyerAVReader * avReader = (Eyer::EyerAVReader *)reader;

    return avReader->PrintInfo();
}