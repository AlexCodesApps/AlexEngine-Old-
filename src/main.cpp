#define DEBUG
#include "includes/IRenderable.hpp"
#include "includes/gamewindow.hpp"
#include "includes/textures.hpp"
#include "includes/time.hpp"
#include <print>

int main() {
    GameWindow::Init();
    auto a = RenderableEntity(Image(Texture::CreateMonoTexture(GameWindow::GetRenderer(), {0, 255, 0, 255})), {16, 16, 36, 30});
    if (!Texture::LoadAll(GameWindow::GetRenderer())) {
        return -1;
    };
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
