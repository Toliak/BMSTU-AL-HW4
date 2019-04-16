#pragma once

#include "Model.h"

class CourseModel: virtual public Model
{
private:
    size_t studentAmount = 0;
    size_t price = 0;

public:

    CourseModel(decltype(CourseModel::studentAmount) studentAmount, decltype(CourseModel::price) price);

    void setStudentAmount(decltype(CourseModel::studentAmount) amount)
    {
        if (amount > 500) {
            throw CourseModelException("CourseModel: Students amount must be below 500");
        }
        CourseModel::studentAmount = amount;
    }

    void setPrice(decltype(CourseModel::price) coursePrice)
    {
        if (coursePrice > 1000000) {
            throw CourseModelException("CourseModel: Price must be below 1000000");
        }
        CourseModel::price = coursePrice;
    }

    decltype(CourseModel::studentAmount) getStudentAmount() const
    {
        return studentAmount;
    }

    decltype(CourseModel::price) getPrice() const
    {
        return price;
    }

    std::string getModelName() const noexcept override
    {
        return "CourseModel";
    }

    std::string toString() const override;

    std::string fromString(const std::string &string) override;
};
