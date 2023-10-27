#include "conversation.h"

#include <iostream>

Conversation::Conversation(const std::shared_ptr<Scene> &scene,
                           std::map<std::string, Dialogue> characters,
                           std::vector<ConversationEntry> script)
    : PhysicalEntity(scene, 0, 0, 400, 200),
      characters(characters),
      script(script),
      entry_index(0),
      started(false),
      finished(false) {}

void Conversation::update() {
    Dialogue &current_character = characters.at(script[entry_index].character);
    current_character.update();
    if (entry_index == script.size() - 1 && !current_character.is_speaking()) {
        finished = true;
    }
}

void Conversation::render() {
    Dialogue &current_character = characters.at(script[entry_index].character);
    current_character.render();
}

void Conversation::fast_forward_current_entry() {
    Dialogue &current_character = characters.at(script[entry_index].character);
    current_character.skip_speaking();
}

void Conversation::next_entry() {
    Dialogue &current_character = characters.at(script[entry_index].character);
    // If this is the first entry, don't advance the counter before playing
    if (!started) {
        speak_entry(entry_index);
        started = true;
        return;
    }
    if (current_character.is_speaking()) {
        current_character.skip_speaking();
    }
    if (entry_index == script.size() - 1) {
        std::cout << "Error: Attempted to play next entry but there are no "
                     "more entries in the script."
                  << std::endl;
        return;
    }
    entry_index += 1;
    speak_entry(entry_index);
}

void Conversation::fast_forward_or_next_entry() {
    Dialogue &current_character = characters.at(script[entry_index].character);
    if (current_character.is_speaking()) {
        fast_forward_current_entry();
    } else {
        next_entry();
    }
}

void Conversation::speak_entry(int index) {
    Dialogue &character = characters.at(script[index].character);
    character.set_text(script[index].text);
    character.speak();
}

bool Conversation::is_finished() { return finished; }

void Conversation::reset_to_beginning() {
    started = false;
    finished = false;
    entry_index = 0;
    Dialogue &character = characters.at(script[entry_index].character);
    character.set_text("");
    character.skip_speaking();
}