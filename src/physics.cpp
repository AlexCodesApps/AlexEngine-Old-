#include "includes/physics.hpp"
#include "SDL2/SDL_rect.h"
#include "includes/entity_resv.hpp"
#include "includes/hitbox.hpp"
#include "includes/renderable.hpp"
#include "includes/sprites.hpp"
#include "includes/time.hpp"
#include "includes/vec2.hpp"
#include <utility>

namespace {
    EntityResv<Physics::Entity, Physics::Entity::ID> PhysicsSprites;
    using PhysIDPair = decltype(PhysicsSprites)::value_type;
}
namespace Physics {
    Entity::ID Entity::New(Sprite::Ref Ref, const Data& Data) {
        return PhysicsSprites.New(Entity{
            .PhysData = Data,
            .SpriteRef = Ref,
        });
    }
    Entity::ID Entity::New(const Entity& Ref) {
        return PhysicsSprites.New(Ref);
    }
    Entity::ID Entity::New() {
        return PhysicsSprites.New();
    }
    Entity& Entity::Get(ID GID) {
        return PhysicsSprites.Get(GID);
    }
    void Entity::Remove(ID RID) {
        PhysicsSprites.Remove(RID);
    }
    void Entity::Update() {
        PhysicsSprites.Foreach([](PhysIDPair& phys1) {
            if (phys1.second.PhysData.Flags & std::to_underlying(Data::Bit::Immobile)) return;
            auto& spr1 = phys1.second.SpriteRef.GetMut();
            Vec2 spr1_velocity_position = {
                spr1.Body.x + (phys1.second.PhysData.Velocity.x * Timer::DeltaTime()),
                spr1.Body.y + (phys1.second.PhysData.Velocity.y * Timer::DeltaTime())
            };
            phys1.second.PhysData.Flags &= ~u8(std::to_underlying(Data::Bit::CollisionLeft) |
                                           std::to_underlying(Data::Bit::CollisionRight)|
                                           std::to_underlying(Data::Bit::CollisionUp)   |
                                           std::to_underlying(Data::Bit::CollisionDown) |
                                           std::to_underlying(Data::Bit::CollidingDangerous));
            phys1.second.PhysData.Velocity.x += (phys1.second.PhysData.Acceleration.x * Timer::DeltaTime());
            phys1.second.PhysData.Velocity.y += (phys1.second.PhysData.Acceleration.y * Timer::DeltaTime());
            PhysicsSprites.Foreach([&phys1, &spr1, &spr1_velocity_position](PhysIDPair& phys2) {
                if (phys1.first == phys2.first
                || (phys1.second.PhysData.Flags & std::to_underlying(Data::Bit::Ghost))
                || (phys2.second.PhysData.Flags & std::to_underlying(Data::Bit::Ghost))) return;
                const auto& spr2 = phys2.second.SpriteRef.Get();
                const Vec2 spr2_position = {spr2.Body.x, spr2.Body.y};
                const SDL_FRect spr2_hitbox_body = phys2.second.PhysData.HitboxToRect(spr2_position);
                if (!Hitbox::IsColliding(
                    phys1.second.PhysData.HitboxToRect(spr1_velocity_position),
                    spr2_hitbox_body)) {
                    return;
                }
                if (phys2.second.PhysData.Flags & std::to_underlying(Data::Bit::Dangerous)) {
                    phys1.second.PhysData.Flags |= std::to_underlying(Data::Bit::CollidingDangerous);
                }
                const SDL_FRect XHitboxTest = phys1.second.PhysData.HitboxToRect({
                    spr1_velocity_position.x,
                    spr1.Body.y
                });
                const SDL_FRect YHitboxTest = phys1.second.PhysData.HitboxToRect({
                    spr1.Body.x,
                    spr1_velocity_position.y
                });
                if (Hitbox::IsColliding(XHitboxTest, spr2_hitbox_body)) {
                    if (phys1.second.PhysData.Velocity.x > 0.0f) {
                        phys1.second.PhysData.Flags |= std::to_underlying(Data::Bit::CollisionRight);
                    }
                    else {
                        phys1.second.PhysData.Flags |= std::to_underlying(Data::Bit::CollisionLeft);
                    }
                    spr1_velocity_position.x = spr1.Body.x;
                    phys1.second.PhysData.Velocity.x = 0;
                }
                if (Hitbox::IsColliding(YHitboxTest, spr2_hitbox_body)) {
                    if (phys1.second.PhysData.Velocity.y > 0.0f) {
                        phys1.second.PhysData.Flags |= std::to_underlying(Data::Bit::CollisionDown);
                    }
                    else {
                        phys1.second.PhysData.Flags |= std::to_underlying(Data::Bit::CollisionUp);
                    }
                    spr1_velocity_position.y = spr1.Body.y;
                    phys1.second.PhysData.Velocity.y = 0;
                }
            });
            SDL_FRectSetXY(spr1.Body, spr1_velocity_position);
        });
    }
    Auto::Auto(Entity::ID Tag)
    : Tag(Tag) {}
    Auto::Auto()
    : Tag(Entity::New(Sprite::New(), {})) {}
    Auto::Auto(Sprite::Ref Ref, const Data& Data)
    : Tag(Entity::New(Ref, Data)) {}
    Auto::Auto(Auto&& Ref)
    : Tag(std::exchange(Ref.Tag, ENTITY_RESV_NULL_ID)) {}
    Auto::~Auto() {
        if (Tag) {
            PhysicsSprites.Remove(Tag);
        }
    }
    Auto& Auto::operator=(Auto&& Ref) {
        std::swap(Tag, Ref.Tag);
        return *this;
    }
    Entity& Auto::Get() {
        return Entity::Get(Tag);
    }
    Auto Auto::Clone(Sprite::Ref Ref) {
        return Auto(Entity::New(Ref, Get().PhysData));
    }
}
