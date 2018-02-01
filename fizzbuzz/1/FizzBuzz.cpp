#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <sstream>

using namespace testing;

class Printer
{
public:
  void print(std::vector<int> input, std::ostream& out)
  {
    if (!input.empty())
        out << input.front() << "\n";
  }
};

struct PrinterTest : public Test
{
    std::stringstream output;
    Printer printer;

};

TEST_F(PrinterTest, ShouldReturnEmptyTextForEmptyInput)
{
  std::vector<int> intput;
  printer.print(intput, output);

  ASSERT_THAT(output.str(), Eq(""));
}

TEST_F(PrinterTest, ShouldPrintNumberFollowedByNewline)
{
  std::vector<int> intput{1};
  printer.print(intput, output);

  ASSERT_THAT(output.str(), Eq("1\n"));
}

int main(int argc, char** argv)
{
  InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
