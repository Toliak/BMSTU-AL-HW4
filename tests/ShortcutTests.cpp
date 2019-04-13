#include "gtest/gtest.h"

#include "Shortcut.h"

TEST(SplitShortcutTest, SplitSuccess)
{
    std::string remain;
    auto result = splitString<int, std::string, double>("1234\nEasy string\n8.776\nremain\n543", '\n', &remain);
    EXPECT_EQ(std::get<0>(result), 1234);
    EXPECT_EQ(std::get<1>(result), "Easy string");
    EXPECT_EQ(std::get<2>(result), 8.776);

    EXPECT_EQ(remain, "remain\n543");
}