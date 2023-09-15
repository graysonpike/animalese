#ifndef ANIMALESE_H
#define ANIMALESE_H

#include <sdlgl/game/entity.h>
#include <sdlgl/game/timer.h>
#include <sdlgl/audio/sound.h>


class Animalese : public Entity {

    std::map<char, Sound> sounds;
    std::string text;
    int text_index;
    Timer sound_timer;
    bool speaking;

    void play_sound_for_char(char c);
    void play_next_sound();

    static const std::map<char, std::string>& get_translation_map();
    static std::map<char, std::string> initialize_translation_map();



public:
    Animalese(const std::shared_ptr<Scene>& scene, const std::string& text);

    void update() override;
    void render() override;

};

#endif
