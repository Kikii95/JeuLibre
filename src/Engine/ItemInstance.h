#pragma once

#include <string>
#include <random>
#include <sstream>
#include <iomanip>

struct ItemInstance {
    std::string itemId;
    int quantity = 1;

    float durability = 100.0f;
    bool identified = true;
    bool isEquipped = false;
    std::string uid;

    ItemInstance(const std::string& id, int qty = 1)
        : itemId(id), quantity(qty), durability(100.0f), identified(true), isEquipped(false) {
        uid = GenerateUID(); 
    }

    static std::string GenerateUID() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, 255);

        std::stringstream ss;
        for (int i = 0; i < 16; ++i) {
            ss << std::hex << std::setw(2) << std::setfill('0') << dist(gen);
        }
        return ss.str();
    }
};
