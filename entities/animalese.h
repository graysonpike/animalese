#ifndef ANIMALESE_H
#define ANIMALESE_H

#include <sdlgl/game/entity.h>
#include <sdlgl/audio/sound.h>

class Animalese : public Entity {

    std::vector<Sound> sounds;

    void play_random_sound();

public:
    Animalese(const std::shared_ptr<Scene>& scene);

    void update() override;
    void render() override;

};

#endif
