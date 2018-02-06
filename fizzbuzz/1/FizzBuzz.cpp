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
    virtual ~FizzBuzzCondition() = default;
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

    std::vector<std::string> create(int numbers = 100)
    {
        std::vector<std::string> output;
        for (int i = 1; i <= numbers; ++i)
        {
            output.push_back(getOutputFor(i));
        }
        return {output};
    }

  private:
    const FizzBuzzCondition& condition;

    std::string getOutputFor(int i)
    {
        const std::string out = constructFizzBuzzOutput(i);
        if (out.empty())
        {
            return std::to_string(i);
        }
        return out;
    }

    std::string constructFizzBuzzOutput(int i)
    {
        std::string out;
        if (shouldFizz(1))
        {
            out += fizz();
        }
        if (shouldBuzz(1))
        {
            out += buzz();
        }
        return out;
    }

    bool shouldFizz(int i)
    {
        return condition.isFizz(i);
    }

    constexpr const char* fizz()
    {
        return "Fizz";
    }

    bool shouldBuzz(int i)
    {
        return condition.isBuzz(i);
    }

    constexpr const char* buzz()
    {
        return "Buzz";
    }
};

struct FizzBuzzCreatorTest : public Test
{
    FizzBuzzCreatorTest()
    {
        EXPECT_CALL(condition, isFizz(_)).WillRepeatedly(Return(false));
        EXPECT_CALL(condition, isBuzz(_)).WillRepeatedly(Return(false));
    }
    MockFizzBuzzCondition condition;
    FizzBuzzCreator creator{condition};
};

TEST_F(FizzBuzzCreatorTest, ShouldReturnNumberIfNotFizzAndNotBuzz)
{
    ASSERT_THAT(creator.create(1), ElementsAre("1"));
}

TEST_F(FizzBuzzCreatorTest, ShouldReturnFizzIfFizzAndNotBuzz)
{
    EXPECT_CALL(condition, isFizz(1)).WillRepeatedly(Return(true));

    ASSERT_THAT(creator.create(1), ElementsAre("Fizz"));
}

TEST_F(FizzBuzzCreatorTest, ShuoldReturnBuzzIfBuzzAndNotFizz)
{
    EXPECT_CALL(condition, isBuzz(1)).WillRepeatedly(Return(true));

    ASSERT_THAT(creator.create(1), ElementsAre("Buzz"));
}

TEST_F(FizzBuzzCreatorTest, ShouldReturnFizzBuzzIfFizzAndBuzz)
{
    EXPECT_CALL(condition, isFizz(1)).WillOnce(Return(true));
    EXPECT_CALL(condition, isBuzz(1)).WillOnce(Return(true));

    ASSERT_THAT(creator.create(1), ElementsAre("FizzBuzz"));
}

TEST_F(FizzBuzzCreatorTest, ShouldReturnMoreElements)
{
    ASSERT_THAT(creator.create(3), ElementsAre("1", "2", "3"));
}

class FizzDivideThreeBuzzDivideByFiveCondition : public FizzBuzzCondition
{
  public:
    bool isFizz(int i) const override
    {
        return !(i % 3);
    }

    bool isBuzz(int i) const override
    {
        return i == 5;
    }
};

TEST(FizzDivideThreeBuzzDivideByFiveConditionTest, IsFizzShouldReturnFalseFor1)
{
    ASSERT_FALSE(FizzDivideThreeBuzzDivideByFiveCondition{}.isFizz(1));
}

TEST(FizzDivideThreeBuzzDivideByFiveConditionTest, IsFizzShouldReturnTrueFor3)
{
    ASSERT_TRUE(FizzDivideThreeBuzzDivideByFiveCondition{}.isFizz(3));
}

TEST(FizzDivideThreeBuzzDivideByFiveConditionTest, IsFizzShouldReturnFalseFor4)
{
    ASSERT_FALSE(FizzDivideThreeBuzzDivideByFiveCondition{}.isFizz(4));
}

TEST(FizzDivideThreeBuzzDivideByFiveConditionTest, IsFizzShouldReturnTrueFor6)
{
    ASSERT_TRUE(FizzDivideThreeBuzzDivideByFiveCondition{}.isFizz(6));
}

TEST(FizzDivideThreeBuzzDivideByFiveConditionTest, IsBuzzShouldReturnFalseFor1)
{
    ASSERT_FALSE(FizzDivideThreeBuzzDivideByFiveCondition{}.isBuzz(1));
}

TEST(FizzDivideThreeBuzzDivideByFiveConditionTest, IsBuzzShouldReturnTrueFor5)
{
    ASSERT_TRUE(FizzDivideThreeBuzzDivideByFiveCondition{}.isBuzz(5));
}

TEST(FizzDivideThreeBuzzDivideByFiveConditionTest, IsBuzzShouldReturnFalseFor6)
{
    ASSERT_FALSE(FizzDivideThreeBuzzDivideByFiveCondition{}.isBuzz(6));
}

int main(int argc, char** argv)
{
    InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
