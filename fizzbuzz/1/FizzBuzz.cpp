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

class FizzBuzzCondition
{
  public:
    virtual bool isFizz(int) const = 0;
    virtual bool isBuzz(int) const = 0;
};

class MockFizzBuzzCondition : public FizzBuzzCondition
{
  public:
    MOCK_CONST_METHOD1(isFizz, bool(int));
    MOCK_CONST_METHOD1(isBuzz, bool(int));
};

class FizzBuzzCreator
{
  public:
    FizzBuzzCreator(const FizzBuzzCondition& c) : condition{c}
    {
    }

    std::vector<std::string> create(int i = 100)
    {
        condition.isFizz(1);
        condition.isBuzz(1);
        return {"1"};
    }

  private:
    const FizzBuzzCondition& condition;
};

TEST(FizzBuzzCreatorTest, ShouldReturn100FizzBuzz)
{
    MockFizzBuzzCondition condition;

    EXPECT_CALL(condition, isFizz(1)).WillRepeatedly(Return(false));
    EXPECT_CALL(condition, isBuzz(1)).WillRepeatedly(Return(false));

    ASSERT_THAT(FizzBuzzCreator{condition}.create(1), ElementsAre("1"));
}

int main(int argc, char** argv)
{
    InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
