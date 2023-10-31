#include "dialogue.h"

#include <sdlgl/graphics/graphics.h>

#include <iostream>

#define DIALOGUE_NAME_TEXT_PADDING_PX (30)

void Dialogue::set_width_and_height_from_screen_size() {
    Graphics &graphics = Graphics::get_instance();
    w = graphics.get_width();
    h = graphics.get_height();
}

void Dialogue::set_face_and_text_positioning() {
    text_x = face.get_width();
    text_y = h - face.get_height() + 30;
    // Draw face snapped to left or right side of screen, depending on `facing`
    if (facing == FacePosition::left) {
        face_x = 0;
    }
    if (facing == FacePosition::right) {
        face_x = w - face.get_width();
    }
    face_y = h - face.get_height();
}

void Dialogue::create_typewriter() {
    int typewriter_y = name.empty() ? 0 : text_y + DIALOGUE_NAME_TEXT_PADDING_PX;
    int typewriter_max_width = w - (2 * face.get_width());
    typewriter = std::make_shared<Typewriter>(
            text_x, typewriter_y, typewriter_max_width, font, text_color);
}

Dialogue::Dialogue(const std::shared_ptr<Scene> &scene,
                   std::shared_ptr<Voice> voice, Texture face, std::string font,
                   SDL_Color text_color, SDL_Color name_color, std::string text,
                   std::string name, FacePosition facing)
    : PhysicalEntity(scene, 0, 0, 0, 0),
      voice(voice),
      face(face),
      font(font),
      text_color(text_color),
      name_color(name_color),
      text(text),
      name(name),
      facing(facing) {
    set_width_and_height_from_screen_size();
    set_face_and_text_positioning();
    create_typewriter();
    set_text(text);
}

void Dialogue::update() {
    voice->update();
    typewriter->update();
}

void Dialogue::render() {
    // If a name is specified, render it. Then render the text lower to
    // accommodate it.
    if (!name.empty()) {
        std::shared_ptr<SDL_Texture> text_texture =
            Graphics::load_font_texture(font, name, name_color);

        int texture_width, texture_height;
        SDL_QueryTexture(text_texture.get(), NULL, NULL, &texture_width,
                         &texture_height);
        int name_x = facing == FacePosition::left ? text_x : face_x - texture_width;
        SDL_Rect dst = {name_x, text_y, texture_width, texture_height};
        SDL_RenderCopy(Graphics::get_instance().get_renderer().get(),
                       text_texture.get(), NULL, &dst);
    }
    face.draw(face_x, face_y);
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