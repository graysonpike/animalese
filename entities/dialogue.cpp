#include "dialogue.h"

#include <iostream>

Dialogue::Dialogue(const std::shared_ptr<Scene> &scene,
                   std::shared_ptr<Voice> voice, Texture face, std::string text)
    : PhysicalEntity(scene, 0, 0, 400, 200), voice(voice), face(face) {
    typewriter = std::make_shared<Typewriter>(x + 200, y + 100);
    set_text(text);
}

void Dialogue::update() {
    voice->update();
    typewriter->update();
}

void Dialogue::render() {
    face.draw(x, y);
    typewriter->render();
}

void Dialogue::speak() {
    voice->speak();
    typewriter->type();
}

void Dialogue::skip_speaking() {
    voice->stop_speaking();
    typewriter->skip_to_end();
}

bool Dialogue::is_speaking() { return voice->is_speaking(); }

void Dialogue::set_text(std::string new_text) {
    this->text = new_text;
    voice->set_text(new_text);
    typewriter->set_text(new_text);
}