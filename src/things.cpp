#include <functional>
#include "things.h"

ThingFactory::ThingFactory(SDL_Renderer* irenderer) {
    renderer = irenderer;
}

Thing* ThingFactory::create(ThingType type) {
    try {
        LOG(DEBUG, "Create thing");
        std::function<Thing*(SDL_Renderer*)> create = types.at(type);
        LOG(DEBUG, "Found create lambda");
        return create(renderer);
    } catch (const out_of_range& oor) {
        LOG(WARN, "Cannot find create lambda");
        return NULL;
    }
}
