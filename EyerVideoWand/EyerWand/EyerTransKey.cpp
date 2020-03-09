#include "EyerWand.hpp"

namespace Eyer
{
    bool EyerTransKey::operator < (const EyerTransKey &key2)
    {
        return t < key2.t;
    }

    EyerTransKey::EyerTransKey()
    {

    }

    EyerTransKey::EyerTransKey(const EyerTransKey & tk)
    {
        *this = tk;
    }

    EyerTransKey & EyerTransKey::operator = (const EyerTransKey & tk)
    {
        t = tk.t;
        x = tk.x;
        y = tk.y;
        z = tk.z;
        return *this;
    }
}