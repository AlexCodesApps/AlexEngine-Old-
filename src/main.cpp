#define DEBUG
#include "includes/IRenderable.hpp"
#include "includes/gamewindow.hpp"
#include "includes/textures.hpp"
#include "includes/time.hpp"
#include "includes/tiles.hpp"
#include "includes/player.hpp"
#include <print>

int main() {
    GameWindow::Init();
    if (!Texture::LoadAll(GameWindow::GetRenderer())) {
        return -1;
    };
    Tiles::Init();
    DEBUG_LOG("Gamewindow Initialized");
    Player::Load();
    while (GameWindow::IsRunning()) {
        Player::Draw();
        GameWindow::PollEvents();
        GameWindow::DrawBuffer();
    }
    Texture::DestroyAll();
    GameWindow::Destroy();
    return 0;
}
