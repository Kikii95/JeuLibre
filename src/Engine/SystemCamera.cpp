#include "pch.h"

SystemCamera::SystemCamera() {}

void SystemCamera::Update(float dt, const std::vector<Entity*>& entities) {
    for (Entity* entity : entities) {
        auto* camera = entity->GetComponent<ComponentCamera>();
        auto* transform = entity->GetComponent<ComponentTransform>();

        if (camera && transform) {
            sf::View view;
            view.setSize({ GameEngine::GetInstance().GetWindowSize() }); 
            view.setCenter({ transform->GetPosition().x + (transform->GetSize().x / 2), transform->GetPosition().y + (transform->GetSize().y / 2) });

            GameEngine::GetInstance().GetWindow().setView(view);
            break; 
        }
    }
}

void SystemCamera::Logs() {
	if (!debugMode || !logSystemCamera) return;
	EntityManager& em = GameEngine::GetInstance().GetEntityManager();
	const auto& entities = em.GetAllEntities();
	int total = 0;
	int cameras = 0;
	for (Entity* e : entities) {
		auto* camera = e->GetComponent<ComponentCamera>();
		if (!camera) continue;
		++total;
		cameras++;
		HEAD("sys_CAMERA") << "Entity " << e->GetID() << " a un composant camera." << ENDL;
	}
	if (total == 0) {
		HEAD("sys_CAMERA") << "Aucune camera trouvee." << ENDL;
	}
}