#include "includes/player.hpp"
#include "SDL2/SDL_rect.h"
#include "includes/IRenderable.hpp"
#include "includes/animation.hpp"
#include "includes/gamewindow.hpp"
#include "includes/textures.hpp"
#include "includes/spritesheet.hpp"

namespace Player {
    constexpr auto Scale = 100;
    using Coord2 = std::pair<SpriteSheet::Coordinates, SpriteSheet::Coordinates>;
    constexpr Coord2 LAnim{{0, 0}, {1, 0}};
    constexpr Coord2 RAnim{{0, 1}, {1, 1}};
    Animator Anim;
    SDL_FPoint PlayerPosition{0,0};
    namespace Camera {
        SDL_FPoint GetRelativePosition(SDL_FPoint ExactPostion)
        { return (ExactPostion - PlayerPosition) + SDL_FPoint{(GameWindow::Width - Scale)/2.0f, (GameWindow::Height - Scale)/2.0f}; }
    }
    void Load() {
        Anim = Animator{
            .Data = {
                .Sheet = SpriteSheet(Texture::Get(Texture::Asset::playerplaceholder_spritesheet)),
                .FrameCoords = {
                    LAnim.first,
                    LAnim.second
                }
            },
            .MSWait = 500,
        };
    }
    const SDL_FPoint& GetPosition() {
        return PlayerPosition;
    }
    void ChangePosition(const SDL_FPoint& NewPoint) {
        PlayerPosition = PlayerPosition + NewPoint;
    }
    void ChangeDirection(Direction Dir) {
        auto& p = (Dir ==  Direction::Left) ? LAnim : RAnim;
        auto& v = Anim.GetCoords();
        v[0] = p.first;
        v[1] = p.second;
    }
    void Draw() {
        GameWindow::DrawSprite(RenderableEntity(Anim.GetFrame(), {
            .x = (GameWindow::Width - Scale)/2.0f,
            .y = (GameWindow::Height - Scale)/2.0f,
            .w = Scale,
            .h = Scale
        }));
    }
    void Update() {
        Anim.Update();
        auto axis = GameWindow::GetInputAxis();
        if (axis.x != 0) {
            Player::ChangeDirection((axis.x < 0) ? Player::Direction::Left : Player::Direction::Right);
            PlayerPosition.x += axis.x;
        }
    }
}
