#include "dialogue.h"

Dialogue::Dialogue(const std::shared_ptr<Scene> &scene, Voice &voice,
                   Texture face, std::vector<std::string> paragraphs)
    : PhysicalEntity(scene, 0, 0, 400, 200),
      voice(voice),
      face(face),
      paragraphs(paragraphs),
      paragraph_index(0) {
    typewriter = Typewriter(x + 200, y + 100);
}

void Dialogue::update() {
    if (Inputs::get_instance().is_key_down_event(SDL_SCANCODE_SPACE)) {
        voice.set_text(paragraphs[paragraph_index]);
        voice.speak();
        typewriter.set_text(paragraphs[paragraph_index]);
        typewriter.type();
        paragraph_index += 1;
        paragraph_index %= paragraphs.size();
    }
    voice.update();
    typewriter.update();
}

void Dialogue::render() {
    face.draw(x, y);
    typewriter.render();
}
