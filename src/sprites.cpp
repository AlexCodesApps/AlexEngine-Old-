#define DEBUG
#include "includes/gamewindow.hpp"
#include "includes/player.hpp"
#include "includes/sprites.hpp"
#include "includes/macros/debug.hpp"
#include "includes/hitbox.hpp"
#include <algorithm>
#include <cstdlib>
#include <vector>

namespace {
    using SprIDPair = std::pair<Sprite::ID, Sprite>;
    std::vector<SprIDPair> GlobalMap;
    Sprite::ID IDCounter = 1;
}

void Sprite::DrawAll() {
    std::ranges::sort(
        GlobalMap,
        [](SprIDPair& f, SprIDPair& s) {
            if (f.second.Layer > s.second.Layer) {
                return true;
            }
            else if (f.second.Layer < s.second.Layer) {
                return false;
            }
            else {
                return f.second.ZOffset > s.second.ZOffset;
            }
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

Sprite::ID Sprite::New(SDL_FRect _Body, Image _IMG, Uint8 _Layer) {
    auto NID = IDCounter++;
    GlobalMap.emplace_back(NID, Sprite{
        .Entity = RenderableEntity(_IMG, {}),
        .Body = _Body,
        .Layer = _Layer
    });
    return NID;
}

void Sprite::Remove(ID RID) {
    auto iter = std::remove_if(
        GlobalMap.begin(),
        GlobalMap.end(),
        [=](SprIDPair& p) {
            return p.first == RID;
        }
    );
    if (iter != GlobalMap.end())
        GlobalMap.erase(iter);
}

Sprite& Sprite::Get(ID GID) {
    auto iter
        = std::ranges::find_if(
            GlobalMap,
            [=](SprIDPair& p) {
                return p.first == GID;
            }
        );
    if (iter != GlobalMap.end()) return iter->second;
    DEBUG_ERROR("Invalid Sprite ID Access");
}

bool Sprite::Colliding(ID CID) {
    auto& b = Get(CID);
    for (auto& [id, spr] : GlobalMap) {
        if (id == CID) continue;
        if (Hitbox::IsColliding(b.Body, spr.Body)) return true;
    }
    return false;
}

void Sprite::DestroyAll() {
    GlobalMap.clear();
}

Sprite::Auto::Auto()
: Tag(Sprite::New()) {}
Sprite::Auto::Auto(Sprite::Auto&& rhs)
: Tag(rhs.Tag) {rhs.Tag = NULL_ID;}
Sprite::Auto::~Auto() {
    if (Tag != NULL_ID) {
        Sprite::Remove(Tag);
    }
}
Sprite::Auto& Sprite::Auto::operator=(Sprite::Auto&& rhs) {
    std::swap(Tag, rhs.Tag);
    return *this;
}
Sprite::Auto Sprite::Auto::Clone() {
    Sprite::Auto NewSprite;
    NewSprite.Get() = Get();
    return NewSprite;
}
Sprite& Sprite::Auto::Get() {
    return Sprite::Get(Tag);
}

Sprite::ID Sprite::Auto::GetID() {
    return Tag;
}
