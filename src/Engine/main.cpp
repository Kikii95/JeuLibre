#include "pch.h"

int main() {
    GameEngine& engine = GameEngine::GetInstance();
    engine.Init();
    engine.Run();
    engine.CleanUp();
    return 0;
}
