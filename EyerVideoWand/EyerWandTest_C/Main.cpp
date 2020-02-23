#include <stdio.h>
#include <gtest/gtest.h>
#include <EyerWand/EyerWand.hpp>
#include <EyerWand/InterfaceC.h>

TEST(EyerWand, Version){
    char version[128];
    int ret = eyer_wand_c_get_version(version);
    ASSERT_EQ(ret, 0) << "eyer_wand_c_get_version fail";
    EyerLog("Eyer Wand Version: %s\n", version);
}

int main(int argc,char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
