#include "gtest/gtest.h"

#include "Model/CourseModel.h"
#include "Exception.h"

class CourseModelTest: public ::testing::Test
{

protected:
    virtual void TearDown()
    {

    }
    virtual void SetUp()
    {

    }

public:
    CourseModel emptyCourse{0,0};

};

TEST_F(CourseModelTest, FromStringSuccess)
{
    std::string remain = emptyCourse.fromString("30\n40\nSimple string");
    EXPECT_EQ(emptyCourse.getStudentAmount(), 30);
    EXPECT_EQ(emptyCourse.getPrice(), 40);
    EXPECT_EQ(remain, "Simple string");
}

TEST_F(CourseModelTest, FromStringFail)
{
    ASSERT_THROW(emptyCourse.fromString("30"), SplitShortcutException);
}