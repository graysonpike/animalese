#ifndef ANIMALESE_DIALOGUE_H
#define ANIMALESE_DIALOGUE_H
#include <sdlgl/game/physical_entity.h>

#include "../components/typewriter.h"
#include "../components/voice.h"

// A dialogue box which displays a character's face alongside text with a
// typewriter effect. Plays Animalese speech audio as the text is typed.
// Multiple paragraphs of text can be provided. Pressing the space bar will
// begin speaking and typing the next paragraph.
class Dialogue : public PhysicalEntity {
   public:
    enum class FacePosition { left, right };
    Dialogue(const std::shared_ptr<Scene> &scene, std::shared_ptr<Voice> voice,
             Texture face, std::string font = "base_text",
             SDL_Color text_color = {0, 0, 0}, SDL_Color name_color = {0, 0, 0},
             std::string text = "", std::string name = "",
             FacePosition facing = FacePosition::left);
    void update() override;
    void render() override;
    void speak();
    bool is_speaking();
    // Stops voice and skips to end of typewriter effect, displaying the full
    // text.
    void skip_speaking();
    void set_text(std::string new_text);

   private:
    std::shared_ptr<Voice> voice;
    std::shared_ptr<Typewriter> typewriter;
    Texture face;
    std::string font;
    SDL_Color text_color;
    SDL_Color name_color;
    std::string text;
    std::string name;
    FacePosition facing;
    int text_x;
    int text_y;
    int face_x;
    int face_y;
};

#endif
