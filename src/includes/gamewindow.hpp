#pragma once
#include <SDL2/SDL.h>
#include "intalias.hpp"
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
    void SetFlags(i32);
    void Init();
    void DrawBuffer();
    void SetDrawColor(SDL_Color);
    void DrawSprite(const RenderableEntity&);
    void DrawSprite(const SDL_FRect&, const Image&);
    bool IsKeyPressed(SDL_Scancode);
    Vec2 GetInputAxis();
    SDL_Renderer * GetRenderer();
    void PollEvents();
    bool IsRunning();
    void Destroy();
}
