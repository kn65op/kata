#include "gtest/gtest.h"

using namespace testing;

TEST(Dummy, D)
{
    ASSERT_TRUE(true);
}

int main(int argc, char **argv) {
    InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
