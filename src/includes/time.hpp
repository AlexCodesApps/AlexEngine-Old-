#include <SDL2/SDL_timer.h>

namespace Timer {
    class Instance {
        Uint64 StartingTime;
        Instance() : StartingTime(SDL_GetTicks64()) {}
        inline Uint64 ElapsedTicks() {
            return SDL_GetTicks64() - StartingTime;
        }
        inline float ElapsedTime() {
            return static_cast<float>(ElapsedTime())/1000.0f;
        }
    };
}
