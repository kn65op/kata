#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <sstream>

using namespace testing;

class Printer
{
public:
    void print(std::vector<int>, std::ostream&)
    {}
};

TEST(PrinterTest, ShouldReturnEmptyTextForEmptyInput)
{
    std::stringstream output;
    std::vector<int> intput;
    Printer{}.print(intput, output);

    ASSERT_THAT(output.str(), Eq(""));
}

int main(int argc, char **argv) {
    InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
