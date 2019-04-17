#include "gtest/gtest.h"

#include "Shortcut.h"

TEST(SplitShortcutTest, SplitSuccess)
{
    std::string remain = "1234\nEasy string\n8.776\nremain\n543";
    auto result = splitString<int, std::string, double>(remain, '\n', &remain);
    EXPECT_EQ(std::get<0>(result), 1234);
    EXPECT_EQ(std::get<1>(result), "Easy string");
    EXPECT_EQ(std::get<2>(result), 8.776);

    EXPECT_EQ(remain, "remain\n543");
}

TEST(SplitShortcutTest, SplitSuccessSingle)
{
    std::string remain = "10";
    auto result = splitString<size_t>(remain, '\n', &remain);

    EXPECT_EQ(std::get<0>(result), static_cast<size_t>(10));
    EXPECT_EQ(remain, std::string(""));
}