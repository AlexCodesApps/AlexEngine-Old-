#pragma once
#include "intalias.hpp"
#include <SDL2/SDL_timer.h>

namespace Timer {
    class Instance {
        u64 StartingTime;
    public:
        Instance() : StartingTime(SDL_GetTicks64()) {}
        inline void ResetTime() {
            StartingTime = SDL_GetTicks64();
        }
        inline u64 ElapsedTicks() const {
            return SDL_GetTicks64() - StartingTime;
        }
        inline f32 ElapsedTime() const {
            return static_cast<f32>(ElapsedTicks())/1000.0f;
        }
    };
    void UpdateDeltaTime();
    f32 DeltaTime();
}
