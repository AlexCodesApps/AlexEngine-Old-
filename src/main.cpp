#include "includes/macroutils.hpp"
#define DEBUG
#include "includes/spritesheet.hpp"
#include "includes/gamewindow.hpp"
#include "includes/textures.hpp"
#include "includes/time.hpp"
#include "includes/player.hpp"

int main() {
    GameWindow::Init();
    if (!Texture::LoadAll(GameWindow::GetRenderer())) {
        GameWindow::Destroy();
        return -1;
    };
    DEBUG_LOG("Gamewindow Initialized");
    Player::Load();
    auto sheet = SpriteSheet(Texture::Get(Texture::Asset::testspritesheet));
    auto tex = sheet.Get({1, 0});
    while (GameWindow::IsRunning()) {
        Player::Update();
        Player::Draw();
        GameWindow::PollEvents();
        GameWindow::DrawBuffer();
        Timer::UpdateDeltaTime();
    }
    Texture::DestroyAll();
    GameWindow::Destroy();
    return 0;
}
