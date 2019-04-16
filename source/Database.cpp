#include "Database.h"
#include "Model/EducationalSubdivisionModel.h"
#include "Model/ScientificSubdivisionModel.h"

std::string HybridDatabase::fromString(const std::string &string)
{
    std::string remain;                                 ///< Отстаток строки
    size_t elementAmount;                               ///< Количество объектов
    std::tie(BaseDatabase::name, elementAmount) = splitString<std::string, size_t>(string, '\n', &remain);

    // Считывание каждой модели
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
    // Каждая модель превращается в строку вида 'Название модели\nИнформация'
    return BaseDatabase::name + std::string("\n") + vectorToString(
        *this,
        [](const BaseSubdivisionModel *baseSubdivision) {
            return baseSubdivision->getModelName() + std::string("\n") + baseSubdivision->toString();
        }
    );
}

HybridDatabase::~HybridDatabase()
{
    for (auto it : static_cast<std::vector<BaseSubdivisionModel *> &>(*this)) {
        delete it;
    }
}
