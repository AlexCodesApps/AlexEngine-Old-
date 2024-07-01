#include "includes/time.hpp"

namespace Timer {
    Instance Elapsed;
    float Delta;
    void UpdateDeltaTime() {
        Delta = Elapsed.ElapsedTime();
        Elapsed.ResetTime();
    }
    float DeltaTime() {
        return Delta;
    }
}
