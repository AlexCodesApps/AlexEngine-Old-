#define DEBUG
#include "includes/entity_resv.hpp"
#include "includes/gamewindow.hpp"
#include "includes/player.hpp"
#include "includes/sprites.hpp"
#include <algorithm>
#include <utility>
#include <cstdlib>

namespace {
    EntityResv<Sprite, Sprite::ID, [](auto& p1, auto& p2) {
        if (p1.second.Layer > p2.second.Layer) {
            return true;
        }
        else if (p1.second.Layer < p2.second.Layer) {
            return false;
        }
        else {
            return p1.second.ZOffset > p2.second.ZOffset;
        }
    }> GlobalMap;
}

void Sprite::DrawAll() {
    GlobalMap.Sort();
    for (auto& [_, sprite] : GlobalMap) {
        auto RenderedPosition = Player::Camera::GetRelativePosition(sprite.Body);
        sprite.Entity.Body.w = sprite.Body.w * sprite.Scale;
        sprite.Entity.Body.h = sprite.Body.h * sprite.Scale;
        sprite.Entity.Body.x = RenderedPosition.x;
        sprite.Entity.Body.y = RenderedPosition.y;
        GameWindow::DrawSprite(sprite.Entity);
    }
}

Sprite::ID Sprite::New(SDL_FRect _Body, Image _IMG, u8 _Layer) {
    return GlobalMap.New(Sprite{
        .Entity = RenderableEntity(_IMG, {}),
        .Body = _Body,
        .Layer = _Layer
    });
}

void Sprite::Remove(ID RID) {
    GlobalMap.Remove(RID);
}

const Sprite& Sprite::Get(ID GID) {
    return GlobalMap.Get(GID);
}

Sprite& Sprite::GetMut(ID GID) {
    return GlobalMap.Get(GID);
}

void Sprite::DestroyAll() {
    GlobalMap.GetContainer().clear();
}

Sprite::Auto::Auto()
: Tag(Sprite::New()) {}
Sprite::Auto::Auto(Sprite::Auto&& rhs)
: Tag(rhs.Tag) {rhs.Tag = null_id;}
Sprite::Auto::~Auto() {
    if (Tag != null_id) {
        Sprite::Remove(Tag);
    }
}

Sprite::Auto& Sprite::Auto::operator=(Sprite::Auto&& rhs) {
    std::swap(Tag, rhs.Tag);
    return *this;
}

Sprite::Auto Sprite::Auto::Clone() {
    Sprite::Auto NewSprite;
    NewSprite.GetMut() = GetMut();
    return NewSprite;
}

Sprite& Sprite::Auto::GetMut() {
    return Sprite::GetMut(Tag);
}

const Sprite& Sprite::Auto::Get() {
    return Sprite::Get(Tag);
}

Sprite::ID Sprite::Auto::ID() {
    return Tag;
}
