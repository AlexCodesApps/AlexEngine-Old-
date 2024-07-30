#include "includes/physics.hpp"
#include "includes/entity_resv.hpp"
#include "includes/macros/macro_utils.hpp"
#include "includes/renderable.hpp"
#include "includes/time.hpp"
#include "includes/vec2.hpp"
#include <utility>

namespace {
    EntityResv<Physics::Inst, Physics::Inst::ID> PhysicsSprites;
    using PhysIDPair = decltype(PhysicsSprites)::value_type;
}
namespace Physics {
    Inst::ID Inst::New() {
        return PhysicsSprites.New();
    }
    Inst& Inst::Get(ID GID) {
        return PhysicsSprites.Get(GID);
    }
    void Inst::Remove(ID RID) {
        PhysicsSprites.Remove(RID);
    }
    void Inst::Update() {
        PhysicsSprites.Foreach([](PhysIDPair& phys1) {
            if (phys1.second.data.Flags & ENUM_TO_INT(Data::Bit::Immobile)) return;
            auto& spr1 = phys1.second.spr.GetMut();
            Vec2 spr1_velocity_position = {
                spr1.Body.x + (phys1.second.data.Velocity.x * Timer::DeltaTime()),
                spr1.Body.y + (phys1.second.data.Velocity.y * Timer::DeltaTime())
            };
            phys1.second.data.Flags &= ~u8(ENUM_TO_INT(Data::Bit::CollisionLeft) |
                                           ENUM_TO_INT(Data::Bit::CollisionRight)|
                                           ENUM_TO_INT(Data::Bit::CollisionUp)   |
                                           ENUM_TO_INT(Data::Bit::CollisionDown));
            phys1.second.data.Velocity.x += (phys1.second.data.Acceleration.x * Timer::DeltaTime());
            phys1.second.data.Velocity.y += (phys1.second.data.Acceleration.y * Timer::DeltaTime());
            PhysicsSprites.Foreach([&phys1, &spr1, &spr1_velocity_position](PhysIDPair& phys2) {
                if (phys1.first == phys2.first
                || (phys1.second.data.Flags & ENUM_TO_INT(Data::Bit::Ghost))
                || (phys2.second.data.Flags & ENUM_TO_INT(Data::Bit::Ghost))) return;
                const auto& spr2 = phys2.second.spr.Get();
                const Vec2 spr2_position = {spr2.Body.x, spr2.Body.y};
                const SDL_FRect spr2_hitbox_body = phys2.second.data.HitboxToRect(spr2_position);
                if (!Hitbox::IsColliding(
                    phys1.second.data.HitboxToRect(spr1_velocity_position),
                    spr2_hitbox_body)) {
                    return;
                }
                const SDL_FRect XHitboxTest = phys1.second.data.HitboxToRect({
                    spr1_velocity_position.x,
                    spr1.Body.y
                });
                const SDL_FRect YHitboxTest = phys1.second.data.HitboxToRect({
                    spr1.Body.x,
                    spr1_velocity_position.y
                });
                if (Hitbox::IsColliding(XHitboxTest, spr2_hitbox_body)) {
                    if (phys1.second.data.Velocity.x > 0.0f) {
                        phys1.second.data.Flags |= ENUM_TO_INT(Data::Bit::CollisionRight);
                    }
                    else {
                        phys1.second.data.Flags |= ENUM_TO_INT(Data::Bit::CollisionLeft);
                    }
                    spr1_velocity_position.x = spr1.Body.x;
                    phys1.second.data.Velocity.x = 0;
                }
                if (Hitbox::IsColliding(YHitboxTest, spr2_hitbox_body)) {
                    if (phys1.second.data.Velocity.y > 0.0f) {
                        phys1.second.data.Flags |= ENUM_TO_INT(Data::Bit::CollisionDown);
                    }
                    else {
                        phys1.second.data.Flags |= ENUM_TO_INT(Data::Bit::CollisionUp);
                    }
                    spr1_velocity_position.y = spr1.Body.y;
                    phys1.second.data.Velocity.y = 0;
                }
            });
            SDL_FRectSetXY(spr1.Body, spr1_velocity_position);
        });
    }
    Inst Inst::Clone() {
        return Inst {
            .data = data,
            .spr = spr.Clone()
        };
    }

    Auto::Auto() {
        Tag = Inst::New();
    }
    Auto::Auto(Inst::ID Tag)
    : Tag(Tag) {}
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
    Inst& Auto::Get() {
        return Inst::Get(Tag);
    }
    Auto Auto::Clone() {
        Inst::ID NewInst = Inst::New();
        Inst::Get(NewInst) = Get().Clone();
        return {NewInst};
    }
}
