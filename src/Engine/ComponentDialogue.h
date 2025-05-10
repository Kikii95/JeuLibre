#pragma once

struct DialogueEntry {
    std::string id;
    std::string text;
    bool repeatable = false;
    bool consumed = false;

    DialogueEntry(const std::string& _id, const std::string& _text, bool _repeatable = false)
        : id(_id), text(_text), repeatable(_repeatable) {
    }
};

class ComponentDialogue : public Component {
public:
    ComponentDialogue(Entity* entity);

    void AddDialogue(const DialogueEntry& dialogue);
    const std::vector<DialogueEntry>& GetDialogues() const;

    void MarkAsConsumed(const std::string& id);
    bool IsDialogueAvailable(const std::string& id) const;

private:
    std::vector<DialogueEntry> dialogues;
};
