#pragma once

#define PRINT(Header, Message) Logs::Get()->Print(Header, Message)
#define HEAD(Header) Logs::Get()->Print(Header, "")
#define OUTPUT *Logs::Get()
#define ENDL "\n"
#define ENDL2 "\n\n"
#define LINE "----------------------------------------------------------------------------------------------------------------------------"

extern bool debugMode;
extern bool logScene;
extern bool logComponent;
extern bool logSystemManager;
extern bool logSystemPhysics;
extern bool logSystemRender;
extern bool logSystemInput;
extern bool logSystemCamera;
extern bool logSystemWeapon;
extern bool logSystemInventory;
extern bool logSystemAI;
extern bool logSystemEvent;
extern bool logSystemGame;
extern bool logSystemAction;
extern bool logSystemBuffDebuff;
extern bool logSystemCombat;
extern bool logSystemDifficulty;
extern bool logSystemCollision;
extern bool logSystemDialogue;
extern bool logSystemHealth;
extern bool logSystemCrewManagement;
extern bool logSystemFaction;
extern bool logSystemFogOfWar;
extern bool logSystemLoot;
extern bool logSystemMerchant;
extern bool logSystemMoney;
extern bool logSystemNavire;
extern bool logSystemProjectile;
extern bool logSystemQuest;
extern bool logSystemReputation;
extern bool logSystemState;
extern bool logSystemTurnOrder;
extern bool logSystemText;
extern bool logSystemSpawner;

class Logs {
private:
    std::ofstream mStream;
    bool mIsInit = false;
    std::mutex logMutex;

    void Print(const char* message);

public:
    Logs() = default;
    ~Logs() { if (mIsInit) mStream.close(); }

    static Logs* Get();

    void Init();
    void UnInit();

    Logs& Print(const char* header, const char* message);
    Logs& operator<<(const char* _other);
    Logs& operator<<(float _other);
    Logs& operator<<(int _other);
};
