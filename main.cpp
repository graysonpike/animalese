#include <sdlgl/audio/audio.h>
#include <sdlgl/audio/sound.h>
#include <sdlgl/game/context.h>
#include <sdlgl/graphics/graphics.h>

#include <fstream>
#include <iostream>

#include "components/voice.h"
#include "dependencies/json.hpp"
#include "entities/conversation.h"
#include "entities/dialogue.h"

// for convenience
using json = nlohmann::json;

std::vector<ConversationEntry> get_script() {
    // Read JSON object from resources file
    std::ifstream file("script.json");
    json paragraphs_json;
    file >> paragraphs_json;
    std::vector<ConversationEntry> script;
    for (json::iterator it = paragraphs_json["script"].begin();
         it != paragraphs_json["script"].end(); it++) {
        script.push_back({it.value()["character"], it.value()["text"]});
    }
    return script;
}

std::shared_ptr<Conversation> create_demo_conversation_entity(
    std::shared_ptr<Scene> scene) {
    // 1.3 and 1.5 are the pitches for male and female respectively
    Texture devika_face =
        Resources::get_instance().get_texture("devika");
    Dialogue devika_dialogue =
        Dialogue(scene, std::make_shared<Voice>(1.3f), devika_face, "base_text",
            {0, 0, 0}, {190, 35, 25}, "", "Devika", Dialogue::FacePosition::left);

    Texture laura_face =
        Resources::get_instance().get_texture("laura");
    Dialogue laura_dialogue = Dialogue(
        scene, std::make_shared<Voice>(1.5f), laura_face, "base_text",
        {0, 0, 0}, {20, 50, 165}, "", "Laura", Dialogue::FacePosition::right);

    std::map<std::string, Dialogue> characters;
    characters.emplace("devika", devika_dialogue);
    characters.emplace("laura", laura_dialogue);

    std::shared_ptr<Conversation> conversation =
        std::make_shared<Conversation>(scene, characters, get_script());
    scene->add_entity(conversation);
    return conversation;
}

int main() {
    Graphics::initialize(720, 480);
    Context context(std::make_shared<Clock>());
    std::shared_ptr<Scene> scene = std::make_shared<Scene>();
    Resources::get_instance().load_resources("resources.json");

    Audio::get_instance();

    std::shared_ptr<Conversation> conversation =
        create_demo_conversation_entity(scene);

    Graphics &graphics = Graphics::get_instance();
    Inputs &inputs = Inputs::get_instance();

    // Enter a simple update loop
    bool loop = true;
    while (loop) {
        inputs.update();
        context.clock->tick();
        graphics.clear_screen((SDL_Color){255, 255, 255, 255});

        scene->update(context.clock->get_delta());
        scene->render();

        graphics.present_renderer(context.clock->get_delta());

        if (inputs.is_key_down_event(SDL_SCANCODE_SPACE)) {
            if (conversation->is_finished()) {
                conversation->reset_to_beginning();
            } else {
                conversation->fast_forward_or_next_entry();
            }
        }

        // If ESC or 'X' button is pressed, leave the update loop and exit
        if (inputs.get_quit()) {
            loop = false;
        }
    }

    return 0;
}