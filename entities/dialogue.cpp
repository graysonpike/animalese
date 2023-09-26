#include "dialogue.h"


Dialogue::Dialogue(const std::shared_ptr<Scene> &scene, Voice &voice, Texture face) : PhysicalEntity(scene, 0, 0, 400, 200), voice(voice), face(face) {}

void Dialogue::update() {
    voice.update();
}

void Dialogue::render() {
    face.draw(x, y);
}