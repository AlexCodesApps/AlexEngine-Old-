#include "includes/gamewindow.hpp"
#include "SDL2/SDL.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_video.h"

namespace GameWindow {
    int KeyBoardLength;
    const Uint8 * KeyboardState = SDL_GetKeyboardState(&KeyBoardLength);
    SDL_Renderer * Renderer;
    SDL_Window * Window;
    Uint32 WindowFlags;
    bool _IsRunning = true;
    void SetFlags(Uint32 flags) {
        WindowFlags = flags;
    }
    void Init() {
        SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER);
        Window = SDL_CreateWindow("Title", 0, 0, LiteralWidth, LiteralHeight, WindowFlags);
        Renderer = SDL_CreateRenderer(Window, -1, 0);
        SDL_RenderSetVSync(Renderer, true);
        SDL_RenderSetLogicalSize(Renderer, LiteralWidth / Scale, LiteralHeight / Scale);
    }
    void DrawBuffer() {
        SDL_RenderPresent(Renderer);
        SetDrawColor(FlushColor);
        SDL_RenderClear(Renderer);
    }
    void SetDrawColor(SDL_Color Color) {
        SDL_SetRenderDrawColor(Renderer, Color.r, Color.g, Color.b, Color.a);
    }
    void DrawSprite(const RenderableEntity& Sprite) {
        SDL_RenderCopyF(Renderer, Asset::GetTexture(Sprite.IMG.ID), &Sprite.IMG.Dimensions, &Sprite.Body);
    }
    void DrawSprite(const SDL_FRect& Body, const Image& IMG) {
        SDL_RenderCopyF(Renderer, Asset::GetTexture(IMG.ID), &IMG.Dimensions, &Body);
    }
    bool IsKeyPressed(SDL_Scancode Key) {
        if (Key >= KeyBoardLength) return false;
        return KeyboardState[Key];
    }
    Vec2 GetInputAxis() {
        Vec2 ReturnAxis{};
        if (KeyboardState[SDL_SCANCODE_UP]) ReturnAxis.y -= 1;
        if (KeyboardState[SDL_SCANCODE_DOWN]) ReturnAxis.y += 1;
        if (KeyboardState[SDL_SCANCODE_LEFT]) ReturnAxis.x -= 1;
        if (KeyboardState[SDL_SCANCODE_RIGHT]) ReturnAxis.x += 1;
        return ReturnAxis;
    }
    SDL_Renderer * GetRenderer() {
        return Renderer;
    }
    void PollEvents() {
        static SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) _IsRunning = false;
        }
    }
    bool IsRunning() {
        return _IsRunning;
    }
    void Destroy() {
        SDL_DestroyWindow(Window);
        SDL_DestroyRenderer(Renderer);
        SDL_Quit();
    }
}
