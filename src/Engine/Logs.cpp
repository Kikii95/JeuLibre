#include "pch.h"

bool debugMode = false;
bool logScene = false;
bool logComponent = false;
bool logSystemManager = false;
bool logSystemPhysics = false;
bool logSystemRender = false;
bool logSystemInput = false;
bool logSystemCamera = false;
bool logSystemWeapon = false;
bool logSystemInventory = false;
bool logSystemAI = false;
bool logSystemEvent = false;
bool logSystemAction = false;
bool logSystemBuffDebuff = false;
bool logSystemCombat = false;
bool logSystemDifficulty = false;
bool logSystemCollision = false;
bool logSystemDialogue = false;
bool logSystemCrewManagement = false;
bool logSystemHealth = false;
bool logSystemFaction = false;
bool logSystemFogOfWar = false;
bool logSystemLoot = false;
bool logSystemMerchant = false;
bool logSystemMoney = false;
bool logSystemNavire = false;
bool logSystemProjectile = false;
bool logSystemQuest = false;
bool logSystemReputation = false;
bool logSystemState = false;
bool logSystemTurnOrder = false;
bool logSystemText = false;
bool logSystemSpawner = true;



Logs* Logs::Get() {
    static Logs log;
    return &log;
}

void Logs::Init() {
    std::lock_guard<std::mutex> lock(logMutex);
    mStream.open("logs.txt");
    mIsInit = true;
}

void Logs::UnInit() {
    std::lock_guard<std::mutex> lock(logMutex);
    if (mStream.is_open()) {
        mStream.close();
    }
    mIsInit = false;
}

Logs& Logs::Print(const char* header, const char* message) {
    if (debugMode) {
        if (!mIsInit) return *this;
        std::lock_guard<std::mutex> lock(logMutex);

        std::cout << "[" << header << "] : " << message << std::endl;
        mStream << "[" << header << "] : " << message << std::endl;
    }
    return *this;
}

void Logs::Print(const char* message) {
    if (debugMode) {
        if (!mIsInit) return;
        std::lock_guard<std::mutex> lock(logMutex);

        std::cout << message;
        mStream << message;
    }
}

Logs& Logs::operator<<(const char* _other) {
    Print(_other);
    return *this;
}

Logs& Logs::operator<<(int _other) {
    Print(std::to_string(_other).c_str());
    return *this;
}

Logs& Logs::operator<<(float _other) {
    Print(std::to_string(_other).c_str());
    return *this;
}
