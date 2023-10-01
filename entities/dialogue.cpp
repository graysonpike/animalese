#include "dialogue.h"

Dialogue::Dialogue(const std::shared_ptr<Scene> &scene, Voice &voice, Texture face)
    : PhysicalEntity(scene, 0, 0, 400, 200), voice(voice), face(face) {
    typewriter = Typewriter(x + 200, y + 100);
}

void Dialogue::update() {
    if (Inputs::get_instance().is_key_down_event(SDL_SCANCODE_SPACE)) {
        std::string text = "Hello! My name is Devika and I am a cutie patootie!";
        voice.set_text(text);
        voice.speak();
        typewriter.set_text(text);
        typewriter.type();
    }
    voice.update();
    typewriter.update();
}

void Dialogue::render() {
    face.draw(x, y);
    typewriter.render();
}
