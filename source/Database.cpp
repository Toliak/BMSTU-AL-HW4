#include "Database.h"

std::string HybridDatabase::fromString(const std::string &string)
{
    std::string remain;
    size_t elementAmount;
    std::tie(BaseDatabase::name, elementAmount) = splitString<std::string, size_t>(string, '\n', &remain);

    for (size_t i = 0; i < elementAmount; i++) {
        std::string modelType;
        std::tie(modelType) = splitString<std::string>(remain, '\n', &remain);

        BaseSubdivisionModel *subdivision;
        if (modelType == "EducationalSubdivisionModel") {
            subdivision = new EducationalSubdivisionModel("", "", 0, 0);
        } else if (modelType == "ScientificSubdivisionModel") {
            subdivision = new ScientificSubdivisionModel("", "", 0, 0);
        } else {
            throw HybridDatabaseException("HybridDatabase: wrong model type");
        }
        remain = subdivision->fromString(remain);
        std::vector<BaseSubdivisionModel *>::emplace_back(subdivision);
    }

    return remain;
}

std::string HybridDatabase::toString() const
{
    return BaseDatabase::name + std::string("\n") + vectorToString(
        *this,
        [](const BaseSubdivisionModel *baseSubdivision) {
            return baseSubdivision->getModelName() + std::string("\n") + baseSubdivision->toString();
        }
    );
}

HybridDatabase::~HybridDatabase()
{

}
