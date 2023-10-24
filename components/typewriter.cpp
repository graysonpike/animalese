#include "typewriter.h"

#include <SDL2/SDL.h>
#include <sdlgl/graphics/graphics.h>

#include <iostream>
#include <utility>

#include "../utilities/text_utils.h"

Typewriter::Typewriter() {}

Typewriter::Typewriter(int x, int y, std::string font, SDL_Color color,
                       float word_duration)
    : x(x),
      y(y),
      font(std::move(font)),
      color(color),
      typing_timer(word_duration),
      typing(false),
      word_index(0) {}

void Typewriter::type() {
    if (!text.empty()) {
        typing = true;
        type_next_word();
    } else {
        std::cout << "Error: Attempted to speak Voice with an empty string."
                  << std::endl;
    }
}

void Typewriter::set_text(const std::string &text) {
    this->text = text;
    words = TextUtils::get_words_from_text(text);
    displayed_text = "";
    word_index = 0;
}

void Typewriter::update() {
    if (typing && typing_timer.is_done()) {
        type_next_word();
    }
}

void Typewriter::render() {
    if (displayed_text.empty()) {
        return;
    }
    std::shared_ptr<SDL_Texture> text_texture =
        Graphics::load_font_texture(font, displayed_text, color, 400);

    int texture_width, texture_height;
    SDL_QueryTexture(text_texture.get(), NULL, NULL, &texture_width,
                     &texture_height);
    SDL_Rect dst = {x, y, texture_width, texture_height};
    SDL_RenderCopy(Graphics::get_instance().get_renderer().get(),
                   text_texture.get(), NULL, &dst);
}

void Typewriter::type_next_word() {
    if (word_index == words.size()) {
        std::cout << "Error: Attempted to type word beyond available text."
                  << std::endl;
        return;
    }
    displayed_text += words[word_index];
    typing_timer.reset();
    word_index++;
    if (word_index == words.size()) {
        word_index = 0;
        typing = false;
    } else {
        displayed_text += " ";
    }
}