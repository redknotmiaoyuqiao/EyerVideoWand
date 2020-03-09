#include "EyerWand.hpp"

namespace Eyer
{
    EyerVideoPanel::EyerVideoPanel()
    {
    }

    EyerVideoPanel::~EyerVideoPanel()
    {
    }

    EyerVideoPanel::EyerVideoPanel(const EyerVideoPanel & panel)
    {
        *this = panel;
    }

    EyerVideoPanel & EyerVideoPanel::operator = (const EyerVideoPanel & panel)
    {
        mvp = panel.mvp;
        frame = panel.frame;
        return *this;
    }

    int EyerVideoPanel::GetYDate(unsigned char * yData)
    {
        frame.GetYData(yData);
        return 0;
    }

    int EyerVideoPanel::GetUDate(unsigned char * uData)
    {
        frame.GetUData(uData);
        return 0;
    }

    int EyerVideoPanel::GetVDate(unsigned char * vData)
    {
        frame.GetVData(vData);
        return 0;
    }

    int EyerVideoPanel::GetW()
    {
        return frame.GetWidth();
    }

    int EyerVideoPanel::GetH()
    {
        return frame.GetHeight();
    }

    int EyerVideoPanel::SetData(EyerAVFrame & _frame)
    {
        frame = _frame;
        return 0;
    }

    EyerMat4x4 EyerVideoPanel::GetMVPMat()
    {
        return mvp;
    }
}