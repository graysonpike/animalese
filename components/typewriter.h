#ifndef ANIMALESE_TYPEWRITER_H
#define ANIMALESE_TYPEWRITER_H

#include <SDL2/SDL.h>
#include <sdlgl/game/timer.h>

#include <string>

// Renders text to the screen one word at a time to give a typewriter effect.
class Typewriter {
   public:
    Typewriter();
    Typewriter(int x, int y, int max_width, std::string font = "base_text",
               SDL_Color color = {0, 0, 0}, float word_duration = 0.08f);
    // Must be called by parent's `update()` function.
    void update();
    // Must be called by parent's `render()` function.
    void render();
    // Sets the text to be typed when `type()` is called.
    void set_text(std::string new_text);
    // Begins typing the currently set text to the screen.
    void type();
    // Stops typewriter effect and immediately displays the full text
    void skip_to_end();

   private:
    int x;
    int y;
    int max_width;
    std::string font;
    SDL_Color color;
    std::string text;
    std::vector<std::string> words;
    int word_index;
    std::string displayed_text;
    Timer typing_timer;
    bool typing;

    void type_next_word();
};

#endif  // ANIMALESE_TYPEWRITER_H
