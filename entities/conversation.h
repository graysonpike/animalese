#ifndef ANIMALESE_CONVERSATION_H
#define ANIMALESE_CONVERSATION_H

#include <sdlgl/game/physical_entity.h>

#include "dialogue.h"

struct ConversationEntry {
    std::string character;
    std::string text;
};

// A conversation between multiple characters. Each character is represented by
// a single Dialogue object. The conversation itself is represented as a script,
// similar to dialogue in a movie script. The script is represented as a list of
// ConversationEntry objects.
class Conversation : public PhysicalEntity {
   public:
    Conversation(const std::shared_ptr<Scene> &scene,
                 std::map<std::string, Dialogue> characters,
                 std::vector<ConversationEntry> script);
    void update() override;
    void render() override;
    // Skip to the end of the current entry being spoken.
    // If no character is speaking, does nothing.
    void fast_forward_current_entry();
    // Begin speaking and typing the next entry.
    // If an entry is currently being spoken, it will be cut off and replaced by
    // the next entry.
    void next_entry();
    // If an entry is being spoken, fast-forward to the end. Otherwise, begin
    // the next entry.
    void fast_forward_or_next_entry();
    bool is_finished();
    void reset_to_beginning();

   private:
    std::map<std::string, Dialogue> characters;
    std::vector<ConversationEntry> script;
    void speak_entry(int index);
    // Represents the entry that is currently being spoken or has completed
    // speaking. If the conversation has not started playing, entry_index will
    // be 0 and started will be false.
    int entry_index;
    bool started;
    bool finished;
};

#endif