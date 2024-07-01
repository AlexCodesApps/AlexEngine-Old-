#include "includes/player.hpp"
#include "includes/IRenderable.hpp"
#include "includes/animation.hpp"
#include "includes/gamewindow.hpp"
#include "includes/textures.hpp"
#include "includes/spritesheet.hpp"

namespace Player {
    constexpr auto Scale = 16;
    using FrameCoords = std::pair<SpriteSheet::Coordinates, SpriteSheet::Coordinates>;
    constexpr FrameCoords LeftIdle{{0, 0}, {1, 0}};
    constexpr FrameCoords RightIdle{{0, 1}, {1, 1}};
    constexpr FrameCoords LeftWalk{{0, 2}, {1, 2}};
    constexpr FrameCoords RightWalk{{0, 3}, {1, 3}};
    Animator Animation;
    Vec2 PlayerPosition{0,0};
    namespace State {
        Action CurrentAction = Action::Idling;
        Direction CurrentDirection = Direction::Left;
    }
    namespace Camera {
        Vec2 GetRelativePosition(SDL_FRect ExactPostion) {
            auto& [x, y, w, h] = ExactPostion;
            return {
                x - PlayerPosition.x + GameWindow::HalfWidth - w/2.0f,
                y - PlayerPosition.y + GameWindow::HalfHeight - h/2.0f,
            };
        }
    }
    void Load() {
        Animation = Animator{
            .Data = {
                .Sheet = SpriteSheet(Texture::Get(Texture::Asset::playerplaceholder_spritesheet)),
                .FrameCoords = {
                    LeftIdle.first,
                    LeftIdle.second
                }
            },
            .MSWait = 500,
        };
    }
    Vec2 GetPosition() {
        return PlayerPosition;
    }
    void SetPosition(Vec2 NewPoint) {
        PlayerPosition = NewPoint;
    }
    void ChangePosition(Vec2 NewPoint) {
        PlayerPosition = PlayerPosition + NewPoint;
    }
    void UpdateAnimation() {
        auto& Frames =
            (State::CurrentDirection == Direction::Left) ?
                (State::CurrentAction == Action::Idling) ?
                    LeftIdle
                    : LeftWalk
                : (State::CurrentAction == Action::Idling) ?
                    RightIdle
                    : RightWalk;
        auto& CurrentFrames = Animation.GetCoords();
        CurrentFrames[0] = Frames.first;
        CurrentFrames[1] = Frames.second;
    }
    void Draw() {
        static auto Entity = RenderableEntity({}, {
            .x = (GameWindow::Width - Scale)/2.0f,
            .y = (GameWindow::Height - Scale)/2.0f,
            .w = Scale,
            .h = Scale
        });
        Entity.IMG = Animation.GetFrame();
        GameWindow::DrawSprite(Entity);
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
            PlayerPosition = PlayerPosition + Vec2(
                axis.x * Timer::DeltaTime() * Speed, 0
            );
        }
        else {
            State::CurrentAction = Action::Idling;
            Animation.MSWait = 500;
        }
        UpdateAnimation();
    }
}
