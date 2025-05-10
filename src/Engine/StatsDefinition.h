#pragma once
struct StatsDefinition {
    std::string id;
    std::unordered_map<std::string, int> values;
    std::string texture;
    std::vector<int> size; 
};
