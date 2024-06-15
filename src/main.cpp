#define DEBUG
#include "includes/IRenderable.hpp"
#include "includes/gamewindow.hpp"
#include "includes/textures.hpp"
#include "includes/time.hpp"
#include "includes/tiles.hpp"
#include <print>

int main() {
    GameWindow::Init();
    if (!Texture::LoadAll(GameWindow::GetRenderer())) {
        return -1;
    };
    Tiles::Init();
    RenderableEntity a = RenderableEntity(Tiles::TestSheet.Get({1, 0}), {20, 20, 40, 40});
    DEBUG_LOG("Gamewindow Initialized");
    while (GameWindow::IsRunning()) {
        GameWindow::DrawSprite(a);
        GameWindow::PollEvents();
        GameWindow::DrawBuffer();
    }
    Texture::DestroyAll();
    GameWindow::Destroy();
    return 0;
}
