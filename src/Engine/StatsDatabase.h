#pragma once
#include "StatsDefinition.h"

class StatsDatabase {
public:
    static StatsDatabase& Get();

    bool LoadFromFile(const std::string& path);
    const StatsDefinition* GetDefinition(const std::string& id) const;

private:
    std::unordered_map<std::string, StatsDefinition> profiles;
};
