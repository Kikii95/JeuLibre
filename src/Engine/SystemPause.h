#pragma once
class SystemPause : public System
{
public :
	SystemPause();

	SystemType GetType() const override { return SystemType::Reactive; }
	void Update(float dt, const std::vector<Entity*>& entities) override;

	void DisplayPauseMenu(Entity* entity);
	void ClearPauseMenu();

	bool IsPauseMenuVisible() const;
	void SetPauseMenuVisible(bool visible);

	void Logs() override;
private:
	bool pauseMenuVisible = false;
};

