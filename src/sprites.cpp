#define DEBUG
#include "includes/gamewindow.hpp"
#include "includes/player.hpp"
#include "includes/sprites.hpp"
#include "includes/macroutils.hpp"
#include <algorithm>
#include <cstdlib>
#include <vector>

using SprIDPair = std::pair<Sprite::ID, Sprite>;
std::vector<SprIDPair> GlobalMap;

Sprite::ID Sprite::IDCounter = 0;

void Sprite::DrawAll() {
    std::sort(
        GlobalMap.begin(),
        GlobalMap.end(),
        [](SprIDPair& f, SprIDPair& s) {
            return f.second.ZOffset < s.second.ZOffset;
        }
    );
    for (auto& [_, sprite] : GlobalMap) {
        auto RenderedPosition = Player::Camera::GetRelativePosition(sprite.Body);
        sprite.Entity.Body = {
            .x = RenderedPosition.x,
            .y = RenderedPosition.y,
            .w = sprite.Body.w * sprite.Scale,
            .h = sprite.Body.h * sprite.Scale,
        };
        GameWindow::DrawSprite(sprite.Entity);
    }
}

Sprite::ID Sprite::New(SDL_FRect _Body, Image _IMG) {
    auto NID = IDCounter++;
    GlobalMap.emplace_back(NID, Sprite{});
    auto& PlayerSprite = GlobalMap.back().second;
    PlayerSprite.Body = _Body;
    PlayerSprite.Entity.IMG = _IMG;
    return NID;
}

void Sprite::Remove(ID RID) {
    GlobalMap.erase(
        std::remove_if(
            GlobalMap.begin(),
            GlobalMap.end(),
            [=](SprIDPair& p) {
                return p.first == RID;
            }
        )
    );
}

Sprite& Sprite::Get(ID GID) {
    auto iter
        = std::find_if(
            GlobalMap.begin(),
            GlobalMap.end(),
            [=](SprIDPair& p) {
                return p.first == GID;
            }
        );
    if (iter != GlobalMap.end()) return iter->second;
    DEBUG_ERROR("Invalid Sprite ID Access");
}
