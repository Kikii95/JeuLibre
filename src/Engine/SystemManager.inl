template <typename T, typename... Args>
T* SystemManager::AddSystem(Args&&... args) {
    static_assert(std::is_base_of<System, T>::value, "T doit etre un sous-type de System");

    std::type_index typeIdx(typeid(T));

    if (systems.find(typeIdx) != systems.end()) {
        return static_cast<T*>(systems[typeIdx].get());
    }

    auto system = std::make_unique<T>(std::forward<Args>(args)...);
    T* systemPtr = system.get();

    switch (systemPtr->GetType()) {
    case SystemType::Active:
        activeSystems.push_back(systemPtr);
        break;
    case SystemType::UI:
        renderSystems.push_back(systemPtr);
        break;
	case SystemType::TurnBased:
		turnBasedSystems.push_back(systemPtr);
		break;
	case SystemType::Reactive:
		reactiveSystems.push_back(systemPtr);
		break;
    default:
        break;
    }

    systems[typeIdx] = std::move(system);
    return systemPtr;
}

template <typename T, typename... Args>
T* SystemManager::RemoveSystem(Args&&... args) {
	static_assert(std::is_base_of<System, T>::value, "T doit etre un sous-type de System");
	std::type_index typeIdx(typeid(T));
	auto it = systems.find(typeIdx);
	if (it != systems.end()) {
		T* systemPtr = static_cast<T*>(it->second.get());
		switch (systemPtr->GetType()) {
		case SystemType::Active:
			activeSystems.erase(std::remove(activeSystems.begin(), activeSystems.end(), systemPtr), activeSystems.end());
			break;
		case SystemType::UI:
			renderSystems.erase(std::remove(renderSystems.begin(), renderSystems.end(), systemPtr), renderSystems.end());
			break;
		case SystemType::TurnBased:
			turnBasedSystems.erase(std::remove(turnBasedSystems.begin(), turnBasedSystems.end(), systemPtr), turnBasedSystems.end());
			break;
		case SystemType::Reactive:
			reactiveSystems.erase(std::remove(reactiveSystems.begin(), reactiveSystems.end(), systemPtr), reactiveSystems.end());
			break;
		default:
			break;
		}
		systems.erase(it);
		return systemPtr;
	}
	return nullptr;
}



template <typename T>
T* SystemManager::GetSystem() {
    std::type_index typeIdx(typeid(T));
    auto it = systems.find(typeIdx);
    return (it != systems.end()) ? static_cast<T*>(it->second.get()) : nullptr;
}

