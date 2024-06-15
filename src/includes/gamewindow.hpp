#pragma once
#include <SDL2/SDL.h>
#include "IRenderable.hpp"

namespace GameWindow {
    constexpr auto Width = 800;
    constexpr auto Height = 600;
    constexpr auto Scale = 1;
    static constexpr SDL_Color FlushColor = {255, 0, 0, 255};
    extern void SetFlags(Uint32);
    extern void Init();
    extern void DrawBuffer();
    extern void SetDrawColor(SDL_Color);
    extern void DrawSprite(const RenderableEntity&);
    extern SDL_FPoint GetInputAxis();
    extern SDL_Renderer * GetRenderer();
    extern void PollEvents();
    extern bool IsRunning();
    extern void Destroy();
}
