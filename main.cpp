#include <sdlgl/audio/audio.h>
#include <sdlgl/audio/sound.h>
#include <sdlgl/game/context.h>
#include <sdlgl/graphics/graphics.h>

#include <fstream>
#include <iostream>

#include "components/voice.h"
#include "dependencies/json.hpp"
#include "entities/dialogue.h"

// for convenience
using json = nlohmann::json;

std::vector<std::string> get_paragraphs_from_json() {
    // Read JSON object from resources file
    std::ifstream file("paragraphs.json");
    json paragraphs_json;
    file >> paragraphs_json;
    std::vector<std::string> paragraphs;
    for (json::iterator it = paragraphs_json["paragraphs"].begin();
         it != paragraphs_json["paragraphs"].end(); it++) {
        paragraphs.push_back(it.value());
    }
    return paragraphs;
}

int main() {
    Graphics::initialize(640, 480);
    Context context(std::make_shared<Clock>());
    std::shared_ptr<Scene> scene = std::make_shared<Scene>();
    Resources::get_instance().load_resources("resources.json");

    Audio::get_instance();

    // 1.3 and 1.5 are the pitches for male and female respectively
    Voice voice = Voice(1.5f);
    Texture devika_face = Resources::get_instance().get_texture("devika");
    scene->add_entity(
        std::make_shared<Dialogue>(scene, voice, devika_face, get_paragraphs_from_json()));

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

        // If ESC or 'X' button is pressed, leave the update loop and exit
        if (inputs.get_quit()) {
            loop = false;
        }
    }

    return 0;
}