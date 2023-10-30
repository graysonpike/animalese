#include "dialogue.h"

#include <iostream>
#include <sdlgl/graphics/graphics.h>

Dialogue::Dialogue(const std::shared_ptr<Scene> &scene,
                   std::shared_ptr<Voice> voice, Texture face, std::string text, FacePosition facing)
    : PhysicalEntity(scene, 0, 0, 0, 0), voice(voice), face(face), facing(facing) {
    Graphics &graphics = Graphics::get_instance();
    // Dialogue renders to fit screen size
    w = graphics.get_width();
    h = graphics.get_height();
    int text_y = h - face.get_height();
    typewriter = std::make_shared<Typewriter>(face.get_width(), text_y, w - (2 * face.get_width()));
    set_text(text);
}

void Dialogue::update() {
    voice->update();
    typewriter->update();
}

void Dialogue::render() {

    // Draw face snapped to left or right side of screen, depending on `facing`
    int face_y = h - face.get_height();
    if (facing == FacePosition::left) {
        face.draw(0, face_y);
    }
    if (facing == FacePosition::right) {
        int face_x = w - face.get_width();
        face.draw(face_x, face_y);
    }
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