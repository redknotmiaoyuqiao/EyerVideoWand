#include "EyerWand.hpp"

#ifdef EYER_PLATFORM_WINDOWS
#include <windows.h>
#else
#include <locale.h>
#endif

namespace Eyer
{
    EyerVideoFragmentText::EyerVideoFragmentText()
    {

    }

    EyerVideoFragmentText::~EyerVideoFragmentText()
    {

    }

    EyerVideoFragmentText::EyerVideoFragmentText(const EyerVideoFragmentText & vft)
    {
        *this = vft;
    }

    EyerVideoFragmentText & EyerVideoFragmentText::operator = (const EyerVideoFragmentText & vft)
    {
        fontPath = vft.fontPath;
        text = vft.text;

        r = vft.r;
        g = vft.g;
        b = vft.b;

        size = vft.size;

        posX = vft.posX;
        posY = vft.posY;

        return *this;
    }

    int EyerVideoFragmentText::GetTextWidth()
    {
        if(text.IsEmpty()){
            return 0;
        }

        char * char_str = text.str;
        int char_strLen = strlen(char_str);

#ifdef EYER_PLATFORM_WINDOWS
        wchar_t * str = nullptr;
        int strLen = MultiByteToWideChar(CP_UTF8, 0, char_str, -1, str, 0);
        str = new wchar_t[strLen];
        MultiByteToWideChar(CP_UTF8, 0, char_str, -1, str, strLen);
#else
        setlocale(LC_CTYPE, "zh_CN.utf8");

        wchar_t * str = nullptr;
        int strLen = mbstowcs(NULL, char_str, 0) + 1;
        str = new wchar_t[strLen];
        int ret = mbstowcs(str, char_str, char_strLen + 1);
#endif

        int x = 0;
        for(int i=0;i<strLen;i++){
            wchar_t c = str[i];

            EyerType typeCreator(fontPath);
            typeCreator.Init();
            int index = typeCreator.GenChar(c, size);
            if(index <= 0){
                continue;
            }

            EyerTypeBitmap bitmap;
            typeCreator.GetCharBitmap(index, &bitmap);

            EyerGLCacheTexture * t = new EyerGLCacheTexture();
            t->texture = nullptr;
            t->width = bitmap.width;
            t->height = bitmap.height;
            t->bearingY = bitmap.bearingY;
            t->bearingX = bitmap.bearingX;
            t->advance = bitmap.advance;

            x += t->width;
            if(i < strLen - 1) {
                x += t->advance / 64 - t->width - t->bearingX;
            }
        }

        delete[] str;

        return x;
    }

    int EyerVideoFragmentText::SetFontPath(EyerString path)
    {
        fontPath = path;
        return 0;
    }

    int EyerVideoFragmentText::SetText(EyerString _text)
    {
        text = _text;
        return 0;
    }

    int EyerVideoFragmentText::SetColor(float _r, float _g, float _b)
    {
        r = _r;
        g = _g;
        b = _b;
        return 0;
    }

    int EyerVideoFragmentText::SetSize(float _size)
    {
        size = _size;
        return 0;
    }

    int EyerVideoFragmentText::SetPos(float _x, float _y)
    {
        posX = _x;
        posY = _y;
        return 0;
    }

    float EyerVideoFragmentText::GetColorR()
    {
        return r;
    }

    float EyerVideoFragmentText::GetColorG()
    {
        return g;
    }

    float EyerVideoFragmentText::GetColorB()
    {
        return b;
    }

    float EyerVideoFragmentText::GetPosX()
    {
        return posX;
    }

    float EyerVideoFragmentText::GetPosY()
    {
        return posY;
    }

    float EyerVideoFragmentText::GetSize()
    {
        return size;
    }

    EyerVideoFragmentType EyerVideoFragmentText::GetType() const
    {
        return EyerVideoFragmentType::VIDEO_FRAGMENT_TEXT;
    }
}