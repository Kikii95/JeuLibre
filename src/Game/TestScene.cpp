#include "pch.h"
#include "TestScene.h"
#include "OptionScene.h"
void TestScene::OnInit()
{
    // Player
    Entity* player = mpGameEngine->GetEntityManager().CreateEntity();
    player->AddComponent<ComponentTransform>(sf::Vector2f(100, 500), sf::Vector2f(NULL, NULL));
    player->AddComponent<ComponentRender>();
    player->AddComponent<ComponentPhysics>();/*
    player->AddComponent<ComponentInput>();*/
    player->AddComponent<ComponentTag>("PLAYER");
    player->AddComponent<ComponentCollider>();

    player->GetComponent<ComponentCollider>()->SetType(ColliderType::Solid);


    // Wall
    Entity* wall = mpGameEngine->GetEntityManager().CreateEntity();
    wall->AddComponent<ComponentTransform>(sf::Vector2f(400, 500), sf::Vector2f(NULL, NULL));
    wall->AddComponent<ComponentRender>();
    wall->AddComponent<ComponentTag>("WALL");
    wall->AddComponent<ComponentCollider>();

    wall->GetComponent<ComponentCollider>()->SetType(ColliderType::Solid);
}

void TestScene::OnEvent(const std::optional<sf::Event>& event)
{
    // Moves
    Entity* player = mpGameEngine->GetEntityManager().GetEntitiesByTag("PLAYER")[0];
    ComponentPhysics* physics = player->GetComponent<ComponentPhysics>();
    ComponentWeapon* weapon = player->GetComponent<ComponentWeapon>();

    sf::Vector2f velocity = physics->GetVelocity();
    bool moving = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        velocity.x = -200;
        moving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        velocity.x = 200;
        moving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        velocity.y = -300;
        moving = true;
    }
    if (!moving) {
        velocity.x = 0;
    }


    //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
    //    mpGameEngine->LaunchScene<OptionScene>;
    //}


    physics->SetVelocity(velocity);

}

void TestScene::OnUpdate()
{
}
