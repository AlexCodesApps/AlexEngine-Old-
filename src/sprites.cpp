#define DEBUG
#include <bitset>
#include "includes/gamewindow.hpp"
#include "includes/player.hpp"
#include "includes/sprites.hpp"
#include "includes/macros/debug.hpp"
#include "includes/hitbox.hpp"
#include <algorithm>
#include <cstdlib>
#include <vector>

namespace {
    using SprBitSet = std::bitset<8>;
    using SprEntry = std::tuple<Sprite::ID, Sprite, SprBitSet>;
    std::vector<SprEntry> GlobalMap;
    Sprite::ID IDCounter = 1;
}

void Sprite::DrawAll() {
    std::ranges::sort(
        GlobalMap,
        [](SprEntry& f, SprEntry& s) {
            if (std::get<Sprite>(f).Layer > std::get<Sprite>(s).Layer) {
                return true;
            }
            else if (std::get<Sprite>(f).Layer < std::get<Sprite>(s).Layer) {
                return false;
            }
            else {
                return std::get<Sprite>(f).ZOffset > std::get<Sprite>(s).ZOffset;
            }
        }
    );
    for (auto& [_, sprite, bits] : GlobalMap) {
        auto RenderedPosition = Player::Camera::GetRelativePosition(sprite.Body);
        if (bits.none()) {
            sprite.Entity.Body.w = sprite.Body.w * sprite.Scale;
            sprite.Entity.Body.h = sprite.Body.h * sprite.Scale;
        }
        else bits[0] = 1;
        sprite.Entity.Body.x = RenderedPosition.x;
        sprite.Entity.Body.y = RenderedPosition.y;
        GameWindow::DrawSprite(sprite.Entity);
    }
}

Sprite::ID Sprite::New(SDL_FRect _Body, Image _IMG, u8 _Layer) {
    auto NID = IDCounter++;
    GlobalMap.emplace_back(NID, Sprite{
        .Entity = RenderableEntity(_IMG, {}),
        .Body = _Body,
        .Layer = _Layer
    }, 0);
    return NID;
}

void Sprite::Remove(ID RID) {
    auto iter = std::remove_if(
        GlobalMap.begin(),
        GlobalMap.end(),
        [=](SprEntry& p) {
            return std::get<Sprite::ID>(p) == RID;
        }
    );
    if (iter != GlobalMap.end())
        GlobalMap.erase(iter);
}

namespace {

SprEntry& _internalGet(Sprite::ID GID) {
    auto iter
        = std::ranges::find_if(
            GlobalMap,
            [=](SprEntry& p) {
                return std::get<Sprite::ID>(p) == GID;
            }
        );
    if (iter != GlobalMap.end()) return *iter;
    DEBUG_ERROR("Invalid Sprite ID Access");
}

}
const Sprite& Sprite::Get(ID GID) {
    return std::get<Sprite>(_internalGet(GID));
}

Sprite& Sprite::GetMut(ID GID) {
    SprEntry& Ref = _internalGet(GID);
    std::get<SprBitSet>(Ref).reset();
    return std::get<Sprite>(Ref);
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
