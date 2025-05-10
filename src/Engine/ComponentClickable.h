#pragma once

class ComponentClickable : public Component {
public:
    ComponentClickable(Entity* entity);

    void SetOnLeftClick(std::function<void()> callback);
    void SetOnRightClick(std::function<void()> callback);

    void OnLeftClick();
    void OnRightClick();

private:
    std::function<void()> onLeftClick;
    std::function<void()> onRightClick;
};
