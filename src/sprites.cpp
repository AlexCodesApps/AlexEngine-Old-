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

Sprite::ID Sprite::New(const SDL_FRect& _Body, const Image& _IMG, u8 _Layer) {
    return GlobalMap.New(Sprite{
        .Entity = RenderableEntity(_IMG, {}),
        .Body = _Body,
        .Layer = _Layer
    });
}

Sprite::ID Sprite::New(const Sprite& Ref) {
    return GlobalMap.New(Ref);
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

bool Sprite::Valid(ID VID) {
    return GlobalMap.Valid(VID);
}

void Sprite::DestroyAll() {
    GlobalMap.GetContainer().clear();
}

Sprite::Auto::Auto(const SDL_FRect& Rect, const Image& IMG, u8 Layer)
: Tag(Sprite::New(Rect, IMG, Layer)) {}
Sprite::Auto::Auto(Sprite::Auto&& rhs)
: Tag(rhs.Tag) {rhs.Tag = ENTITY_RESV_NULL_ID;}
Sprite::Auto::~Auto() {
    if (Tag != ENTITY_RESV_NULL_ID) {
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

Sprite::ID Sprite::Auto::GetID() {
    return Tag;
}

Sprite::Ref::Ref(Sprite::ID ID)
: Tag(ID) {}

const Sprite& Sprite::Ref::Get() {
    return Sprite::Get(Tag);
}

Sprite& Sprite::Ref::GetMut() {
    return Sprite::GetMut(Tag);
}

bool Sprite::Ref::Valid() {
    return Sprite::Valid(Tag);
}

Sprite::ID Sprite::Ref::GetID() {
    return Tag;
}
