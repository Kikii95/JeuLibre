#pragma once
#include "SpawnerDefinition.h"

class SpawnerDatabase {
public:
    static SpawnerDatabase& Get();

    bool LoadFromFile(const std::string& path);
    const std::vector<SpawnerDefinition>& GetAll() const;

private:
    std::vector<SpawnerDefinition> spawners;
};
