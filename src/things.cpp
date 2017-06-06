#include <functional>
#include "things.h"

ThingFactory::ThingFactory(SDL_Renderer* irenderer) {
    renderer = irenderer;
}

Thing* ThingFactory::create(ThingType type) {
    try {
        Utils::log(DEBUG, "Create thing");
        std::function<Thing*(SDL_Renderer*)> create = types.at(type);
        Utils::log(DEBUG, "Found create lambda");
        return create(renderer);
    } catch (const out_of_range& oor) {
        Utils::log(WARN, "Cannot find create lambda");
        return NULL;
    }
}
