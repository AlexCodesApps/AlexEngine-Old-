#include "includes/time.hpp"

namespace Timer {
    Instance Elapsed;
    f32 Delta;
    void UpdateDeltaTime() {
        Delta = Elapsed.ElapsedTime();
        Elapsed.ResetTime();
    }
    f32 DeltaTime() {
        return Delta;
    }
}
