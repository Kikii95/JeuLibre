#pragma once
#include <string>

enum class ActionType {
	Unknown,
    Use,
    Gather,
    Inspect,
    Interact
};

struct ActionData {
    std::string id;         
    std::string name;         
    std::string effectId;   
    std::string itemId;     
    bool consumeItem = false;
    ActionType actionType = ActionType::Unknown;
    int value = 0;          
};

