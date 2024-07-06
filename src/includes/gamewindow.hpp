#pragma once
#include <SDL2/SDL.h>
#include "renderable.hpp"

namespace GameWindow {
    constexpr auto LiteralWidth = 800;
    constexpr auto LiteralHeight = 600;
    constexpr auto Scale = 4;
    constexpr auto Width = 200;
    constexpr auto Height = 150;
    constexpr auto HalfWidth = Width/2.0f;
    constexpr auto HalfHeight = Height/2.0f;
    static constexpr SDL_Color FlushColor = {0, 0, 255, 255};
    extern void SetFlags(Uint32);
    extern void Init();
    extern void DrawBuffer();
    extern void SetDrawColor(SDL_Color);
    extern void DrawSprite(const RenderableEntity&);
    extern void DrawSprite(const SDL_FRect&, const Image&);
    extern bool IsKeyPressed(SDL_Scancode);
    extern Vec2 GetInputAxis();
    extern SDL_Renderer * GetRenderer();
    extern void PollEvents();
    extern bool IsRunning();
    extern void Destroy();
}
