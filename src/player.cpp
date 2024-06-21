#include "includes/player.hpp"
#include "includes/IRenderable.hpp"
#include "includes/gamewindow.hpp"
#include "includes/textures.hpp"

namespace Player {
    RenderableEntity PlayerEntity;
    SDL_FPoint PlayerPosition{0,0};
    namespace Camera {
        SDL_FPoint GetRelativePosition(SDL_FPoint ExactPostion)
        { return ExactPostion - PlayerPosition; }
    }
    void Load() {
        PlayerEntity = RenderableEntity(
            Image(Texture::Get(Texture::Asset::playerplaceholder), {0, 0, 16, 16}),
            {GameWindow::Width/2.0f, GameWindow::Height/2.0f, 16, 16}
        );
    }
    const SDL_FPoint& GetPosition() {
        return PlayerPosition;
    }
    void ChangePosition(const SDL_FPoint& NewPoint) {
        PlayerPosition = PlayerPosition + NewPoint;
    }
    const RenderableEntity& GetSprite() {
        return PlayerEntity;
    }
    void Draw() {
        GameWindow::DrawSprite(PlayerEntity);
    }
}
