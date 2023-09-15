#include <iostream>
#include <random>
#include "animalese.h"


int random_int(int low, int high) {
    static std::mt19937 eng{std::random_device{}()};
    std::uniform_int_distribution<> distr(low, high);
    return distr(eng);
}


Animalese::Animalese(const std::shared_ptr<Scene>& scene) : Entity(scene) {
    const std::shared_ptr<Resources>& resources = scene->get_graphics()->get_resources();
    std::vector<std::string> sound_names = resources->get_sounds();
    for (std::string& sound_name : sound_names) {
        sounds.push_back(resources->get_sound(sound_name));
    }
}

void Animalese::play_random_sound() {
    scene->get_audio()->play_sound(sounds[random_int(0, sounds.size()-1)]);
}

void Animalese::update() {
    if(scene->get_inputs()->is_key_down_event(SDL_SCANCODE_SPACE)){
        play_random_sound();
    }
}

void Animalese::render() {}