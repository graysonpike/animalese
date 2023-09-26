#include <sdlgl/game/physical_entity.h>
#include "../components/voice.h"


class Dialogue : public PhysicalEntity {
    Voice &voice;
    Texture face;
public:
    Dialogue(const std::shared_ptr<Scene> &scene, Voice &voice, Texture face);
    void update() override;
    void render() override;
};