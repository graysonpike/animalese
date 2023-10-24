#include <sdlgl/game/physical_entity.h>

#include "../components/typewriter.h"
#include "../components/voice.h"

// A dialogue box which displays a character's face alongside text with a
// typewriter effect. Plays Animalese speech audio as the text is typed.
// Multiple paragraphs of text can be provided. Pressing the space bar will
// begin speaking and typing the next paragraph.
class Dialogue : public PhysicalEntity {
   public:
    Dialogue(const std::shared_ptr<Scene> &scene, Voice &voice, Texture face,
             std::vector<std::string> paragraphs);
    void update() override;
    void render() override;

   private:
    Voice &voice;
    Typewriter typewriter;
    Texture face;
    std::vector<std::string> paragraphs;
    int paragraph_index;
};