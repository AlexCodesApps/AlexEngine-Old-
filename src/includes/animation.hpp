#pragma once
#include "intalias.hpp"
#include "spritesheet.hpp"
#include "time.hpp"
#include <vector>

struct AnimationData {
    SpriteSheet Sheet;
    std::vector<SpriteSheet::Coordinates> FrameCoords;
    u64 FrameIndex = 0;
    Image GetFrame();
    void AdvanceFrame();
};

struct Animator {
    AnimationData Data;
    u64 MSWait;
    Timer::Instance Timer;
public:
    void Update();
    void Update(RenderableEntity&);
    std::vector<SpriteSheet::Coordinates>& GetCoords();
    Image GetFrame();
};
