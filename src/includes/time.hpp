#include <SDL2/SDL_timer.h>

namespace Timer {
    class Instance {
        Uint64 StartingTime;
    public:
        Instance() : StartingTime(SDL_GetTicks64()) {}
        inline void ResetTime() {
            StartingTime = SDL_GetTicks64();
        }
        inline Uint64 ElapsedTicks() const {
            return SDL_GetTicks64() - StartingTime;
        }
        inline float ElapsedTime() const {
            return static_cast<float>(ElapsedTime())/1000.0f;
        }
    };
}
