#pragma once
#include "spritesheet.hpp"
#include "time.hpp"
#include <vector>

struct AnimationData {
    SpriteSheet Sheet;
    std::vector<SpriteSheet::Coordinates> FrameCoords;
    size_t FrameIndex = 0;
    Image GetFrame();
    void AdvanceFrame();
};

struct Animator {
    AnimationData Data;
    size_t MSWait;
    Timer::Instance Timer;
public:
    void Update();
    void Update(RenderableEntity&);
    std::vector<SpriteSheet::Coordinates>& GetCoords();
    Image GetFrame();
};
