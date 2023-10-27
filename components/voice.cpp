#include "voice.h"

#include <sdlgl/audio/sound.h>
#include <sdlgl/utilities/random.h>

#include <cctype>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include "../utilities/text_utils.h"

Voice::Voice(float pitch, float word_duration)
    : text_index(0),
      sound_timer(Timer(word_duration)),
      speaking(false),
      pitch(pitch) {
    for (const auto &kv : translation_map) {
        Sound sound = Sound("kiza_kana/" + kv.second, 2);
        sound.set_pitch(pitch);
        sounds.emplace(kv.first, sound);
    }
}

void Voice::set_text(std::string new_text) {
    if (speaking) {
        std::cout
            << "Warning, tried to set text while speaking. Skipping speaking."
            << std::endl;
        stop_speaking();
    }
    this->text = shorten_text(new_text);
}

void Voice::speak() {
    text_index = 0;
    if (text.empty()) {
        std::cout << "Error: Attempted to speak Voice with an empty string."
                  << std::endl;
        return;
    }
    speaking = true;
    play_next_sound();
}

void Voice::update() {
    if (speaking && sound_timer.is_done()) {
        play_next_sound();
        sound_timer.reset();
    }
}

bool Voice::is_speaking() { return speaking; }

void Voice::stop_speaking() { speaking = false; }

void Voice::play_sound_for_char(char c) {
    Sound &sound = sounds.at(c);
    sound.set_pitch(Random::randfloat(pitch - 0.05f, pitch + 0.05f));
    sound.play();
}

void Voice::play_next_sound() {
    char next_char = TextUtils::to_lowercase(text[text_index]);
    play_sound_for_char(next_char);
    text_index++;
    if (text_index == text.size()) {
        speaking = false;
    }
    sound_timer.reset();
}

std::string Voice::shorten_text(const std::string &text) {
    std::istringstream iss(text);
    std::string word;
    std::string result;

    while (iss >> word) {
        std::string cleaned_word;
        for (char c : word) {
            if (std::isalpha(c)) {
                cleaned_word += c;
            }
        }
        if (!cleaned_word.empty()) {
            result += std::string(1, cleaned_word[0]);
        }
    }
    return result;
}

const std::map<char, std::string> Voice::translation_map = {
    {'a', "Voice_Kiza_Kana_a - Voice_Kiza_KanaEx_aa - Voice_Kiza_Loop_a.wav"},
    {'b', "Voice_Kiza_Kana_bo.wav"},
    {'c', "Voice_Kiza_Kana_ha.wav"},
    {'d', "Voice_Kiza_Kana_di.wav"},
    {'e', "Voice_Kiza_Kana_e - Voice_Kiza_KanaEx_ee.wav"},
    {'f', "Voice_Kiza_Kana_fe.wav"},
    {'g', "Voice_Kiza_Kana_ga.wav"},
    {'h', "Voice_Kiza_Kana_ha.wav"},
    {'i', "Voice_Kiza_Kana_i - Voice_Kiza_KanaEx_ii.wav"},
    {'j', "Voice_Kiza_Kana_ja.wav"},
    {'k', "Voice_Kiza_Kana_ka.wav"},
    {'l', "Voice_Kiza_KanaEx_ewo.wav"},
    {'m', "Voice_Kiza_Kana_ma.wav"},
    {'n', "Voice_Kiza_Kana_na.wav"},
    {'o', "Voice_Kiza_Kana_o - Voice_Kiza_KanaEx_oo.wav"},
    {'p', "Voice_Kiza_Kana_pa.wav"},
    {'q', "Voice_Kiza_Kana_ku.wav"},
    {'r', "Voice_Kiza_Kana_ra.wav"},
    {'s', "Voice_Kiza_KanaEx_ehi.wav"},
    {'t', "Voice_Kiza_Kana_ta.wav"},
    {'u', "Voice_Kiza_Kana_u - Voice_Kiza_KanaEx_uu.wav"},
    {'v', "Voice_Kiza_Kana_bi.wav"},
    {'w', "Voice_Kiza_Kana_wa.wav"},
    {'x', "Voice_Kiza_KanaEx_ehe.wav"},
    {'y', "Voice_Kiza_Kana_ya.wav"},
    {'z', "Voice_Kiza_Kana_za.wav"}};