#include <sdlgl/game/clock.h>
#include <sdlgl/game/context.h>
#include <sdlgl/game/scene.h>
#include <sdlgl/graphics/graphics.h>
#include <sdlgl/input/inputs.h>

#include "entities/animalese.h"


void game_loop(const Context& context, const std::shared_ptr<Scene>& scene) {

    context.inputs->update();
    context.clock->tick();
    context.graphics->clear_screen((SDL_Color){255, 255, 255, 255});

    scene->update(context.clock->get_delta());
    scene->render();

    context.audio->update(context.clock->get_delta());

    if (context.inputs->get_quit()) {
        *context.loop = false;
    }

    context.graphics->present_renderer(context.clock->get_delta());

}


int main() {

    Context context(std::make_shared<Graphics>(640, 480),
                    std::make_shared<Audio>(), std::make_shared<Inputs>(),
                    std::make_shared<Clock>());

    context.graphics->get_resources()->load_resources("resources.json");

    std::shared_ptr<Scene> scene = std::make_shared<Scene>(context.graphics, context.audio, context.inputs);

    scene->add_entity(std::make_shared<Animalese>(scene));

    while (*context.loop) {
        game_loop(context, scene);
    }

    return 0;

}