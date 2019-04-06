#include "Database.h"

std::string HybridDatabase::fromString(const std::string &string)
{
    std::string remain;
    size_t elementAmount;
    std::tie(BaseDatabase::name, elementAmount) = splitString<std::string, size_t>(string, '\n', &remain);

    for (size_t i = 0; i < elementAmount; i++) {
        std::string modelType;
        std::tie(modelType) = splitString<std::string>(remain, '\n', &remain);

        BaseSubdivision *subdivision;
        if (modelType == "EducationalSubdivision") {
            subdivision = new EducationalSubdivision("","",0,0);
        } else if (modelType == "ScientificSubdivision") {
            subdivision = new ScientificSubdivision("","",0,0);
        } else {
            throw HybridDatabaseException("HybridDatabase: wrong model type");
        }
        remain = subdivision->fromString(remain);
        std::vector<BaseSubdivision*>::emplace_back(subdivision);
    }

    return remain;
}

std::string HybridDatabase::toString() const
{
    return BaseDatabase::name + std::string("\n") + vectorToString(
        *this,
        [](const BaseSubdivision * const baseSubdivision) {
            return baseSubdivision->getModelName() + std::string("\n") + baseSubdivision->toString();
        }
    );
}
