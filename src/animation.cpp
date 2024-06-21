#include "includes/animation.hpp"

Image AnimationData::GetFrame() {
    Image img = Sheet.Get(FrameCoords[FrameIndex]);
    return img;
}

void AnimationData::AdvanceFrame() {
    FrameIndex++;
    if (FrameIndex >= FrameCoords.size()) FrameIndex = 0;
}

void Animator::Update() {
    if (Timer.ElapsedTicks() >= MSWait) {
        Timer.ResetTime();
        Data.AdvanceFrame();
    }
}

Image Animator::GetFrame() {
    return Data.GetFrame();
}

std::vector<SpriteSheet::Coordinates>& Animator::GetCoords() {
    return Data.FrameCoords;
}
