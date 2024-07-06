#include "includes/player.hpp"
#include "includes/assets.hpp"
#include "includes/renderable.hpp"
#include "includes/animation.hpp"
#include "includes/gamewindow.hpp"
#include "includes/macroutils.hpp"
#include "includes/sprites.hpp"
#include "includes/spritesheet.hpp"

namespace Player {
    using FrameCoords = std::pair<SpriteSheet::Coordinates, SpriteSheet::Coordinates>;
    constexpr FrameCoords LeftIdle{{0, 0}, {1, 0}};
    constexpr FrameCoords RightIdle{{0, 1}, {1, 1}};
    constexpr FrameCoords LeftWalk{{0, 2}, {1, 2}};
    constexpr FrameCoords RightWalk{{0, 3}, {1, 3}};
    constexpr FrameCoords StateTable[] = {LeftIdle, LeftWalk, RightIdle, RightWalk};
    Animator Animation = {
        .Data = {
            .Sheet = (Asset::ImageID::Carl_spritesheet),
            .FrameCoords = {
                LeftIdle.first,
                LeftIdle.second
            }
        },
        .MSWait = 500,
        .Timer{}
    };
    Sprite::ID PlayerID = Sprite::New();
    Sprite& PlayerSprite() {
        return Sprite::Get(PlayerID);
    }
    namespace State {
        Action CurrentAction = Action::Idling;
        Direction CurrentDirection = Direction::Left;
    }
    namespace Camera {
        Vec2 GetRelativePosition(SDL_FRect ExactPostion) {
            auto& [x, y, w, h] = ExactPostion;
            return {
                x - PlayerSprite().Body.x + GameWindow::HalfWidth - w/2.0f,
                y - PlayerSprite().Body.y + GameWindow::HalfHeight - h/2.0f,
            };
        }
    }
    Vec2 GetPosition() {
        return {PlayerSprite().Body.x, PlayerSprite().Body.y};
    }
    void SetPosition(Vec2 NewPoint) {
        SDL_FRectSetXY(PlayerSprite().Body, NewPoint);
    }
    void ChangePosition(Vec2 NewPoint) {
        PlayerSprite().Body.x += NewPoint.x;
        PlayerSprite().Body.y += NewPoint.y;
    }
    void UpdateAnimation() {
        auto& Frames = StateTable[((ENUM_TO_NUMBER(State::CurrentDirection) << 1) | ENUM_TO_NUMBER(State::CurrentAction))];
        auto& CurrentFrames = Animation.GetCoords();
        CurrentFrames[0] = Frames.first;
        CurrentFrames[1] = Frames.second;
        PlayerSprite().Entity.IMG = Animation.GetFrame();
    }
    void Update() {
        Animation.Update();
        auto axis = GameWindow::GetInputAxis();
        if (axis.x != 0) {
            State::CurrentDirection = (axis.x < 0) ?
                Direction::Left
                : Direction::Right;
            State::CurrentAction = Action::Walking;
            Animation.MSWait = 250;
            auto NewPosition = Vec2(
                PlayerSprite().Body.x + axis.x * Timer::DeltaTime() * Speed,
                PlayerSprite().Body.y + 0
            );
            SDL_FRectSetXY(PlayerSprite().Body, NewPosition);
        }
        else {
            State::CurrentAction = Action::Idling;
            Animation.MSWait = 500;
        }
        UpdateAnimation();
    }
}
