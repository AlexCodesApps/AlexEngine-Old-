#include "SDL2/SDL_rect.h"
#include "includes/IRenderable.hpp"
#define DEBUG
#include "includes/spritesheet.hpp"
#include "includes/gamewindow.hpp"
#include "includes/textures.hpp"
#include "includes/time.hpp"
#include "includes/player.hpp"
#include <print>

int main() {
    GameWindow::Init();
    if (!Texture::LoadAll(GameWindow::GetRenderer())) {
        GameWindow::Destroy();
        return -1;
    };
    DEBUG_LOG("Gamewindow Initialized");
    Player::Load();
    auto sheet = SpriteSheet(Texture::Get(Texture::Asset::testspritesheet));
    SDL_FPoint pos = {16, 0};
    auto tex = sheet.Get({1, 0});
    while (GameWindow::IsRunning()) {
        auto p = Player::Camera::GetRelativePosition(pos);
        auto r = RenderableEntity(sheet.Get({1, 0}), {p.x, p.y, 100, 100});
        GameWindow::DrawSprite(r);
        Player::Update();
        Player::Draw();
        GameWindow::PollEvents();
        GameWindow::DrawBuffer();
    }
    Texture::DestroyAll();
    GameWindow::Destroy();
    return 0;
}
