#ifndef VOICE_H
#define VOICE_H

#include <sdlgl/game/entity.h>
#include <sdlgl/game/timer.h>
#include <sdlgl/audio/sound.h>


class Voice {

    std::map<char, Sound> sounds;
    std::string text;
    float pitch;
    int text_index;
    Timer sound_timer;
    bool speaking;

    char to_lowercase(char c);
    std::string shorten_word(const std::string& str);
    std::string shorten_text(const std::string& text);
    void play_sound_for_char(char c);
    void play_next_sound();

    static const std::map<char, std::string>& get_translation_map();
    static std::map<char, std::string> initialize_translation_map();



public:
    explicit Voice(float pitch = 1.5f);
    void set_text(const std::string &text);
    void speak();
    void update();

};

#endif
