#include <utility>
#define DEBUG
#include "SDL2/SDL_scancode.h"
#include "includes/tilemap.hpp"
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
    Sprite::Auto PlayerHandle({0, 0, 16, 16}, Asset::ImageID::Carl);
    Physics::Auto EntityHandle = Physics::Auto(PlayerHandle.GetID(), {
        .Hitbox = {
            .x = 2,
            .y = 0,
            .w = 11,
            .h = 16
        },
        .Acceleration = {.x = 0, .y = 120},
    });
    namespace State {
        Action CurrentAction = Action::Idling;
        Direction CurrentDirection = Direction::Left;
        bool HasJumped = false;
    }
    namespace Camera {
        Vec2 GetRelativePosition(const SDL_FRect& ExactPostion) {
            const Sprite& PlayerSprite = PlayerHandle.Get();
            return {
                ExactPostion.x - PlayerSprite.Body.x + GameWindow::HalfWidth - ExactPostion.w/2.0f,
                ExactPostion.y - PlayerSprite.Body.y + GameWindow::HalfHeight - ExactPostion.h/2.0f,
            };
        }
    }
    Vec2 GetPosition() {
        const auto& PlayerSprite = PlayerHandle.Get();
        return {PlayerSprite.Body.x, PlayerSprite.Body.y};
    }
    void SetPosition(Vec2 NewPoint) {
        SDL_FRectSetXY(PlayerHandle.GetMut().Body, NewPoint);
    }
    void ChangePosition(Vec2 NewPoint) {
        Sprite& PlayerSprite = PlayerHandle.GetMut();
        PlayerSprite.Body.x += NewPoint.x;
        PlayerSprite.Body.y += NewPoint.y;
    }
    void UpdateAnimation() {
        const auto& Frames = StateTable[(std::to_underlying(State::CurrentDirection) << 1) | std::to_underlying(State::CurrentAction)];
        auto& CurrentFrames = Animation.GetCoords();
        CurrentFrames[0] = Frames.first;
        CurrentFrames[1] = Frames.second;
        PlayerHandle.GetMut().Entity.IMG = Animation.GetFrame();
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
        auto& Entity = EntityHandle.Get();
        if (Entity.PhysData.Flags & std::to_underlying(Physics::Data::Bit::CollidingDangerous)) {
            DEBUG_LOG("COLLIDED DANGEROUS");
            GameWindow::ForceQuit();
            return;
        }
        if (Entity.PhysData.Flags & std::to_underlying(Physics::Data::Bit::CollisionDown)) {
            State::HasJumped = false;
        }
        Entity.PhysData.Velocity.x = MovementAxis.x * IntermittentOffset * 80;
        if (MovementAxis.y == 1 && (!State::HasJumped)) {
            State::HasJumped = true;
            Entity.PhysData.Velocity.y = - 160 * IntermittentOffset;
        }
        UpdateAnimation();
    }

    bool OnLuckyBlock() {
        const Sprite& PlayerSprite = PlayerHandle.Get();
        return Tilemap::GetPositionTileID({PlayerSprite.Body.x + 8, PlayerSprite.Body.y + 8}) == 7;
    }
}
