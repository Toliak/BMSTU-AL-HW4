#pragma once

#include "Model.h"

class ProjectModel: virtual public Model
{
private:
    std::string name;
    size_t price = 0;

public:
    ProjectModel(std::string name, decltype(ProjectModel::price) price);

    void setName(std::string projectName)
    {
        ProjectModel::name = std::move(projectName);
    }

    void setPrice(decltype(ProjectModel::price) projectPrice)
    {
        if (projectPrice > 1000000) {
            throw ProjectModelException("ProjectModel: Price must be below 1000000");
        }
        ProjectModel::price = projectPrice;
    }

    const std::string &getName() const noexcept
    {
        return ProjectModel::name;
    }

    decltype(ProjectModel::price) getPrice() const noexcept
    {
        return ProjectModel::price;
    }

    std::string getModelName() const noexcept override
    {
        return "ProjectModel";
    }

    std::string toString() const override;

    std::string fromString(const std::string &string) override;
};
