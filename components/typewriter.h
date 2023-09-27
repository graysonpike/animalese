#ifndef ANIMALESE_TYPEWRITER_H
#define ANIMALESE_TYPEWRITER_H

#include <SDL2/SDL.h>
#include <sdlgl/game/timer.h>

#include <string>

class Typewriter {
    int x;
    int y;
    std::string font;
    SDL_Color color;
    std::string text;
    std::vector<std::string> words;
    int word_index;
    std::string displayed_text;
    Timer typing_timer;
    bool typing;

    void type_next_word();
    static float get_typing_duration_for_word(const std::string& word);

   public:
    Typewriter();
    Typewriter(int x, int y, std::string font = "base_text",
               SDL_Color color = {0, 0, 0});
    void set_text(const std::string &text);
    void type();
    void update();
    void render();
};

#endif  // ANIMALESE_TYPEWRITER_H
