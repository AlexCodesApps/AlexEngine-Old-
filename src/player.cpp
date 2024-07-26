#include "SDL2/SDL_rect.h"
#define DEBUG
#include "includes/hitbox.hpp"
#include "includes/player.hpp"
#include "includes/assets.hpp"
#include "includes/renderable.hpp"
#include "includes/animation.hpp"
#include "includes/gamewindow.hpp"
#include "includes/sprites.hpp"
#include "includes/spritesheet.hpp"
#include "includes/time.hpp"
#include "includes/macros/debug.hpp" // IWYU pragma: keep

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
    Sprite::Auto Player;
    namespace State {
        Action CurrentAction = Action::Idling;
        Direction CurrentDirection = Direction::Left;
    }
    namespace Camera {
        Vec2 GetRelativePosition(SDL_FRect ExactPostion) {
            auto& [x, y, w, h] = ExactPostion;
            Sprite& PlayerSprite = Player.Get();
            return {
                x - PlayerSprite.Body.x + GameWindow::HalfWidth - w/2.0f,
                y - PlayerSprite.Body.y + GameWindow::HalfHeight - h/2.0f,
            };
        }
    }
    Vec2 GetPosition() {
        return {Player.Get().Body.x, Player.Get().Body.y};
    }
    void SetPosition(Vec2 NewPoint) {
        SDL_FRectSetXY(Player.Get().Body, NewPoint);
    }
    void ChangePosition(Vec2 NewPoint) {
        Sprite& PlayerSprite = Player.Get();
        PlayerSprite.Body.x += NewPoint.x;
        PlayerSprite.Body.y += NewPoint.y;
    }
    void UpdateAnimation() {
        auto& Frames = StateTable[((ENUM_TO_INT(State::CurrentDirection) << 1) | ENUM_TO_INT(State::CurrentAction))];
        auto& CurrentFrames = Animation.GetCoords();
        CurrentFrames[0] = Frames.first;
        CurrentFrames[1] = Frames.second;
        Player.Get().Entity.IMG = Animation.GetFrame();
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
        }
        else {
            State::CurrentAction = Action::Idling;
            Animation.MSWait = 500;
        }
        float IntermittentOffset = Timer::DeltaTime() * Speed;
        SDL_FRect& PlayerBody = Player.Get().Body;
        Vec2 MovementAxis = GameWindow::GetInputAxis();
        Vec2 NewPosition = {
            PlayerBody.x + MovementAxis.x * IntermittentOffset,
            PlayerBody.y + (MovementAxis.y + 0.8f) * IntermittentOffset
        };
        const auto XCheck = Vec2{
            NewPosition.x,
            PlayerBody.y,
        };
        const auto YCheck = Vec2{
            PlayerBody.x,
            NewPosition.y
        };
        if (!Hitbox::TilePositionColliding16(XCheck)) PlayerBody.x = NewPosition.x;
        if (!Hitbox::TilePositionColliding16(YCheck)) PlayerBody.y = NewPosition.y;
        UpdateAnimation();
    }
}
