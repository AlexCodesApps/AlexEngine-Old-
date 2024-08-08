#define DEBUG
#include "includes/physics.hpp"
#include "includes/tilemap.hpp"
#include "includes/sprites.hpp"
#include "includes/player.hpp"
#include "includes/gamewindow.hpp"
#include "includes/assets.hpp"
#include "includes/time.hpp"
#include "includes/macros/debug.hpp"

static_assert(sizeof(int) == sizeof(i32));

i32 main() {
    GameWindow::Init();
    if (!Asset::LoadAll(GameWindow::GetRenderer())) {
        GameWindow::Destroy();
        return -1;
    };
    DEBUG_LOG("Gamewindow Initialized");
    Tilemap::Load();
    while (GameWindow::IsRunning()) {
        Player::Update();
        Physics::Entity::Update();
        if (Player::OnLuckyBlock()) {
            if (!Tilemap::IsLastLevel())
                Tilemap::Next();
            else GameWindow::ForceQuit();
        }
        Sprite::DrawAll();
        GameWindow::PollEvents();
        GameWindow::DrawBuffer();
        Timer::UpdateDeltaTime();
    }
    Asset::DestroyAll();
    GameWindow::Destroy();
    return 0;
}
