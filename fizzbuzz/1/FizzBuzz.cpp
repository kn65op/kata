#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <sstream>

using namespace testing;

class Printer
{
  public:
    void print(std::vector<std::string> input, std::ostream& out)
    {
        std::for_each(input.begin(), input.end(), [&](const auto& in) { out << in << "\n"; });
    }
};

struct PrinterTest : public Test
{
    std::stringstream output;
    Printer printer;
};

TEST_F(PrinterTest, ShouldReturnEmptyTextForEmptyInput)
{
    std::vector<std::string> intput;
    printer.print(intput, output);

    ASSERT_THAT(output.str(), Eq(""));
}

TEST_F(PrinterTest, ShouldPrintTextFollowedByNewline)
{
    std::vector<std::string> intput{"1"};
    printer.print(intput, output);

    ASSERT_THAT(output.str(), Eq("1\n"));
}

TEST_F(PrinterTest, ShouldPrintMoreTextFollowedByNewline)
{
    std::vector<std::string> intput{"2", "a"};
    printer.print(intput, output);

    ASSERT_THAT(output.str(), Eq("2\na\n"));
}

class FizzBuzzCreator
{
public:
    std::vector<std::string> create()
    {
        return {};
    }
};

TEST(FizzBuzzCreatorTest, ShouldReturn100FizzBuzz)
{
    ASSERT_THAT(FizzBuzzCreator{}.create(), ElementsAre());
}

int main(int argc, char** argv)
{
    InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
