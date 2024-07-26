#define DEBUG
#include "includes/tilemap.hpp"
#include "includes/sprites.hpp"
#include "includes/player.hpp"
#include "includes/gamewindow.hpp"
#include "includes/assets.hpp"
#include "includes/time.hpp"
#include "includes/macros/debug.hpp"

int main() {
    GameWindow::Init();
    if (!Asset::LoadAll(GameWindow::GetRenderer())) {
        GameWindow::Destroy();
        return -1;
    };
    DEBUG_LOG("Gamewindow Initialized");
    Tilemap::Load();
    while (GameWindow::IsRunning()) {
        Player::Update();
        Sprite::DrawAll();
        GameWindow::PollEvents();
        GameWindow::DrawBuffer();
        Timer::UpdateDeltaTime();
    }
    Asset::DestroyAll();
    GameWindow::Destroy();
    return 0;
}
