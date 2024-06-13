#include "includes/gamewindow.hpp"
#include "SDL2/SDL_keyboard.h"
#include "SDL2/SDL_rect.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_scancode.h"
#include "SDL2/SDL_stdinc.h"

namespace GameWindow {
    const Uint8 * KeyboardState = SDL_GetKeyboardState(NULL);
    SDL_Renderer * Renderer;
    SDL_Window * Window;
    Uint32 WindowFlags;
    bool _IsRunning = true;
    void SetFlags(Uint32 flags) {
        WindowFlags = flags;
    }
    void Init() {
        SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
        Window = SDL_CreateWindow("Title", 0, 0, Width, Height, WindowFlags);
        Renderer = SDL_CreateRenderer(Window, -1, 0);
        SDL_RenderSetVSync(Renderer, true);
    }
    void DrawBuffer() {
        SDL_RenderPresent(Renderer);
        SetDrawColor(FlushColor);
        SDL_RenderClear(Renderer);
    }
    void SetDrawColor(SDL_Color Color) {
        SDL_SetRenderDrawColor(Renderer, Color.r, Color.b, Color.g, Color.a);
    }
    void DrawSprite(const RenderableEntity& Sprite) {
        SDL_RenderCopyF(Renderer, Sprite.IMG.Texture, &Sprite.IMG.Dimensions, &Sprite.Body);
    }
    SDL_FPoint GetInputAxis() {
        SDL_FPoint ReturnAxis = {0};
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
        SDL_Quit();
    }
}
