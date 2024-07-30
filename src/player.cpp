#define DEBUG
#include "SDL2/SDL_scancode.h"
#include "includes/tilemap.hpp"
#include "includes/macros/macro_utils.hpp"
#include "includes/physics.hpp"
#include "includes/player.hpp"
#include "includes/assets.hpp"
#include "includes/renderable.hpp"
#include "includes/animation.hpp"
#include "includes/gamewindow.hpp"
#include "includes/sprites.hpp"
#include "includes/spritesheet.hpp"
#include "includes/time.hpp"
#include "includes/macros/debug.hpp" // IWYU pragma: keep
#include "includes/macros/defer.hpp"

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
    Physics::Auto PhysPlayer;
    DEFER_CALL(([]{
        PhysPlayer.Get().data = {
            .Hitbox = {
                .x = 2,
                .y = 0,
                .w = 11,
                .h = 16
            },
            .Velocity = {},
            .Acceleration = {.x = 0, .y = 120},
            .Flags = {}
        };
    }));
    namespace State {
        Action CurrentAction = Action::Idling;
        Direction CurrentDirection = Direction::Left;
        bool HasJumped = false;
    }
    namespace Camera {
        Vec2 GetRelativePosition(SDL_FRect ExactPostion) {
            const auto& [x, y, w, h] = ExactPostion;
            const Sprite& PlayerSprite = PhysPlayer.Get().spr.Get();
            return {
                x - PlayerSprite.Body.x + GameWindow::HalfWidth - w/2.0f,
                y - PlayerSprite.Body.y + GameWindow::HalfHeight - h/2.0f,
            };
        }
    }
    Vec2 GetPosition() {
        const auto& PlayerSprite = PhysPlayer.Get().spr.Get();
        return {PlayerSprite.Body.x, PlayerSprite.Body.y};
    }
    void SetPosition(Vec2 NewPoint) {
        SDL_FRectSetXY(PhysPlayer.Get().spr.GetMut().Body, NewPoint);
    }
    void ChangePosition(Vec2 NewPoint) {
        Sprite& PlayerSprite = PhysPlayer.Get().spr.GetMut();
        PlayerSprite.Body.x += NewPoint.x;
        PlayerSprite.Body.y += NewPoint.y;
    }
    void UpdateAnimation() {
        auto& Frames = StateTable[((ENUM_TO_INT(State::CurrentDirection) << 1) | ENUM_TO_INT(State::CurrentAction))];
        auto& CurrentFrames = Animation.GetCoords();
        CurrentFrames[0] = Frames.first;
        CurrentFrames[1] = Frames.second;
        PhysPlayer.Get().spr.GetMut().Entity.IMG = Animation.GetFrame();
    }
    void Update() {
        Animation.Update();
        SDL_Point MovementAxis = {
            -GameWindow::IsKeyPressed(SDL_SCANCODE_LEFT) + GameWindow::IsKeyPressed(SDL_SCANCODE_RIGHT),
            GameWindow::IsKeyPressed(SDL_SCANCODE_SPACE)
        };
        if (MovementAxis.x != 0) {
            State::CurrentDirection = (MovementAxis.x < 0) ?
                Direction::Left
                : Direction::Right;
            State::CurrentAction = Action::Walking;
            Animation.MSWait = 250;
        }
        else {
            State::CurrentAction = Action::Idling;
            Animation.MSWait = 500;
        }
        f32 IntermittentOffset = Timer::DeltaTime() * Speed;
        auto& PhysInst = PhysPlayer.Get();
        auto& Data = PhysInst.data;
        if (Data.Flags & ENUM_TO_INT(Physics::Data::Bit::CollisionDown)) {
            State::HasJumped = false;
        }
        auto& Velocity = Data.Velocity;
        Velocity.x = MovementAxis.x * IntermittentOffset * 80;
        if (MovementAxis.y == 1 && (!State::HasJumped)) {
            State::HasJumped = true;
            Velocity.y = - 160 * IntermittentOffset;
        }
        const auto& PlayerSpr = PhysInst.spr.Get();
        if (Tilemap::GetTileID(Tilemap::MapWorldF(Vec2{PlayerSpr.Body.x + 8, PlayerSpr.Body.y + 8})) == 7) {
            Tilemap::Next();
        }
        UpdateAnimation();
    }
}
