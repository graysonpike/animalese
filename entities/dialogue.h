#include <sdlgl/game/physical_entity.h>

#include "../components/voice.h"
#include "../components/typewriter.h"

class Dialogue : public PhysicalEntity {
    Voice &voice;
    Typewriter typewriter;
    Texture face;

   public:
    Dialogue(const std::shared_ptr<Scene> &scene, Voice &voice, Texture face);
    void update() override;
    void render() override;
};