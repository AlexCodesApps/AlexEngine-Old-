#include "includes/gamewindow.hpp"

namespace GameWindow {
    i32 KeyBoardLength;
    const u8 * KeyboardState = SDL_GetKeyboardState(&KeyBoardLength);
    SDL_Renderer * Renderer;
    SDL_Window * Window;
    u32 WindowFlags;
    bool _IsRunning = true;
    void SetFlags(u32 flags) {
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

    void ForceQuit() {
        _IsRunning = false;
    }
}
