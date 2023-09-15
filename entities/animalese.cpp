#include <iostream>
#include <random>
#include <map>
#include <string>
#include <sstream>
#include <cctype>
#include "animalese.h"

char to_lowercase(char c) {
    return std::tolower(static_cast<unsigned char>(c));
}

int random_int(int low, int high) {
    static std::mt19937 eng{std::random_device{}()};
    std::uniform_int_distribution<> distr(low, high);
    return distr(eng);
}

std::string shorten_word(const std::string& str) {
    if (str.size() > 1) {
        return std::string(1, str[0]) + str[str.size() - 1];
    }
    return str;
}

std::string shorten_text(const std::string& text) {
    std::istringstream iss(text);
    std::string word;
    std::string result;

    while (iss >> word) {
        std::string cleanedWord;
        for (char c : word) {
            if (std::isalpha(c)) {  // Check if the character is a letter
                cleanedWord += c;
            }
        }
        result += shorten_word(cleanedWord);
    }

    return result;
}

Animalese::Animalese(const std::shared_ptr<Scene>& scene, const std::string& text) : Entity(scene), text(shorten_text(text)), text_index(0), sound_timer(Timer(0.08f)), speaking(false) {
    const std::map<char, std::string>& translation_map = get_translation_map();
    for (const auto& kv : translation_map) {
        sounds[kv.first] = scene->get_graphics()->get_resources()->get_sound(kv.second);
    }
}

const std::map<char, std::string> &Animalese::get_translation_map() {
    static const std::map<char, std::string> translation_map = initialize_translation_map();
    return translation_map;
}

std::map<char, std::string> Animalese::initialize_translation_map() {
    std::map<char, std::string> m;
    m['a'] = "a";
    m['b'] = "ba";
    m['c'] = "ka";
    m['d'] = "da";
    m['e'] = "e";
    m['f'] = "fe";
    m['g'] = "ga";
    m['h'] = "ha";
    m['i'] = "i";
    m['j'] = "ja";
    m['k'] = "ka";
    m['l'] = "ewo";
    m['m'] = "ma";
    m['n'] = "na";
    m['o'] = "o";
    m['p'] = "pa";
    m['q'] = "ku";
    m['r'] = "ra";
    m['s'] = "sa";
    m['t'] = "ta";
    m['u'] = "u";
    m['v'] = "bi";
    m['w'] = "wa";
    m['x'] = "ehe";
    m['y'] = "ya";
    m['z'] = "za";
    return m;
}

void Animalese::play_sound_for_char(char c) {
    scene->get_audio()->play_sound(sounds[c]);
}

void Animalese::play_next_sound() {
    std::cout << "Playing next sound" << std::endl;
    play_sound_for_char(to_lowercase(text[text_index]));
    text_index ++;
    if (text_index == text.size()) {
        text_index = 0;
        speaking = false;
    }
}

void Animalese::update() {
    if(scene->get_inputs()->is_key_down_event(SDL_SCANCODE_SPACE)){
        speaking = true;
        play_next_sound();
        sound_timer.reset();
    }
    if (speaking && sound_timer.is_done()) {
        play_next_sound();
        sound_timer.reset();
    }
}

void Animalese::render() {}