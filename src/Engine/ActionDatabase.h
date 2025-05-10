#pragma once
#include "ActionDefinition.h"

class ActionDatabase {
public:
    static ActionDatabase& Get();

    bool LoadFromFile(const std::string& path);
    const ActionData* GetAction(const std::string& id) const;

private:
    std::unordered_map<std::string, ActionData> actions;
};
