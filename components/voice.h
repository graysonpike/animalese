#ifndef VOICE_H
#define VOICE_H

#include <sdlgl/audio/sound.h>
#include <sdlgl/game/entity.h>
#include <sdlgl/game/timer.h>

// Plays Animalese audio for any given text.
// Can be re-set with different text for repeated use.
class Voice {
   public:
    explicit Voice(float pitch = 1.5f, float word_duration = 0.08f);
    // Sets the text that will be spoken when `speak()` is called.
    void set_text(const std::string &text);
    // Begins playing Animalese for the currently set text.
    void speak();
    // Must be called as part of parent's `update()` function.
    void update();

   private:
    std::map<char, Sound> sounds;
    std::string text;
    float pitch;
    int text_index;
    Timer sound_timer;
    bool speaking;

    void play_sound_for_char(char c);
    void play_next_sound();
    static const std::map<char, std::string> &get_translation_map();
    static std::map<char, std::string> initialize_translation_map();
    // Given a string of text, returns a shortened version where all words are
    // reduced to their first character and non-alphabetical characters are
    // removed. Characters are lowercased. For example
    // "Hello world." becomes "h w".
    static std::string shorten_text(const std::string &text);
};

#endif
