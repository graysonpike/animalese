#include "voice.h"

#include <sdlgl/audio/sound.h>
#include <sdlgl/utilities/random.h>

#include <cctype>
#include <iostream>
#include <map>
#include <string>

#include "../utilities/text_utils.h"

Voice::Voice(float pitch)
    : text_index(0), sound_timer(Timer(0.08f)), speaking(false), pitch(pitch) {
    const std::map<char, std::string> &translation_map = get_translation_map();
    for (const auto &kv : translation_map) {
        Sound sound = Sound("kiza_kana/" + kv.second, 2);
        sound.set_pitch(pitch);
        sounds.emplace(kv.first, sound);
    }
}

void Voice::set_text(const std::string &text) {
    this->text = TextUtils::shorten_text(text);
    text_index = 0;
}

void Voice::speak() {
    if (!text.empty()) {
        speaking = true;
        play_next_sound();
    } else {
        std::cout << "Error: Attempted to speak Voice with an empty string."
                  << std::endl;
    }
}

void Voice::play_sound_for_char(char c) {
    try {
        Sound &sound = sounds.at(c);
        sound.set_pitch(Random::randfloat(pitch - 0.05f, pitch + 0.05f));
        sound.play();
    } catch (const std::out_of_range &) {
        // Handle the error or do nothing if you expect some keys to be missing
    }
}

void Voice::play_next_sound() {
    char next_char = TextUtils::to_lowercase(text[text_index]);
    play_sound_for_char(next_char);
    text_index++;
    if (text_index == text.size()) {
        text_index = 0;
        speaking = false;
    }
    sound_timer.reset();
}

void Voice::update() {
    if (speaking && sound_timer.is_done()) {
        play_next_sound();
        sound_timer.reset();
    }
}

const std::map<char, std::string> &Voice::get_translation_map() {
    static const std::map<char, std::string> translation_map =
        initialize_translation_map();
    return translation_map;
}

std::map<char, std::string> Voice::initialize_translation_map() {
    std::map<char, std::string> m;
    m['a'] = "Voice_Kiza_Kana_a - Voice_Kiza_KanaEx_aa - Voice_Kiza_Loop_a.wav";
    m['b'] = "Voice_Kiza_Kana_bo.wav";
    m['c'] = "Voice_Kiza_Kana_ha.wav";
    m['d'] = "Voice_Kiza_Kana_di.wav";
    m['e'] = "Voice_Kiza_Kana_e - Voice_Kiza_KanaEx_ee.wav";
    m['f'] = "Voice_Kiza_Kana_fe.wav";
    m['g'] = "Voice_Kiza_Kana_ga.wav";
    m['h'] = "Voice_Kiza_Kana_ha.wav";
    m['i'] = "Voice_Kiza_Kana_i - Voice_Kiza_KanaEx_ii.wav";
    m['j'] = "Voice_Kiza_Kana_ja.wav";
    m['k'] = "Voice_Kiza_Kana_ka.wav";
    m['l'] = "Voice_Kiza_KanaEx_ewo.wav";
    m['m'] = "Voice_Kiza_Kana_ma.wav";
    m['n'] = "Voice_Kiza_Kana_na.wav";
    m['o'] = "Voice_Kiza_Kana_o - Voice_Kiza_KanaEx_oo.wav";
    m['p'] = "Voice_Kiza_Kana_pa.wav";
    m['q'] = "Voice_Kiza_Kana_ku.wav";
    m['r'] = "Voice_Kiza_Kana_ra.wav";
    m['s'] = "Voice_Kiza_KanaEx_ehi.wav";
    m['t'] = "Voice_Kiza_Kana_ta.wav";
    m['u'] = "Voice_Kiza_Kana_u - Voice_Kiza_KanaEx_uu.wav";
    m['v'] = "Voice_Kiza_Kana_bi.wav";
    m['w'] = "Voice_Kiza_Kana_wa.wav";
    m['x'] = "Voice_Kiza_KanaEx_ehe.wav";
    m['y'] = "Voice_Kiza_Kana_ya.wav";
    m['z'] = "Voice_Kiza_Kana_za.wav";
    return m;
}