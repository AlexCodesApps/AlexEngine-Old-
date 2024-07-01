#include "IRenderable.hpp"

struct WorldEntity {
    RenderableEntity Renderer;
    SDL_FRect Body;
    float Scale;
};
