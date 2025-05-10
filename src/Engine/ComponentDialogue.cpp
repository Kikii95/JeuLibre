#include "pch.h"

ComponentDialogue::ComponentDialogue(Entity* entity)
    : Component(entity) {
}

void ComponentDialogue::AddDialogue(const DialogueEntry& dialogue) {
    dialogues.push_back(dialogue);
}

const std::vector<DialogueEntry>& ComponentDialogue::GetDialogues() const {
    return dialogues;
}

void ComponentDialogue::MarkAsConsumed(const std::string& id) {
    for (auto& d : dialogues) {
        if (d.id == id) {
            d.consumed = true;
            return;
        }
    }
}

bool ComponentDialogue::IsDialogueAvailable(const std::string& id) const {
    for (const auto& d : dialogues) {
        if (d.id == id) {
            return !d.consumed || d.repeatable;
        }
    }
    return false;
}
