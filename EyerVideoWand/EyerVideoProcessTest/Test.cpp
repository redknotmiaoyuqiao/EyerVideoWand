#include <gtest/gtest.h>

#include "EyerCore/EyerCore.hpp"
#include "EyerVideoProcess/EyerVideoProcess.hpp"


#include "EyerVPAudioTrackTest.hpp"

#include "EyerVPReadImageTest.h"
#include "EyerVPAudioResTest.hpp"

int main(int argc,char **argv)
{
    RedLog("This is Test\n");
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
