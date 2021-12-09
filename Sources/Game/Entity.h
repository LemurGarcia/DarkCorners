
#pragma once
#include "Sprite.h"
#include <glm/glm.hpp>

class Entity
{
public:
    explicit Entity(Pos pos, Size size = Size{ 1 });

    bool IsCollide(const Entity& entity) const;
    virtual void Update(uint64_t delta);

    float GetAngle() const;

    Entity& operator+=(Pos pos);
    Entity& operator-=(Pos pos);

    Entity& operator+=(Vel vel);
    Entity& operator-=(Vel vel);

    Entity& operator+=(float angle);
    Entity& operator-=(float angle);

    operator Size() const;
    operator Pos() const;
    operator Vel() const;

    void Set(Pos pos);
    void Set(Vel vel);
    void Set(Size size);
    void Set(float angle);

protected:
    Pos m_pos;
    Size m_size;
    Vel m_vel{0};
    float m_angle = 0.0f;
};

class Renderable
{
public:
    ~Renderable() = default;
    void Render(const Entity& camera);

protected:
    virtual Sprite& GetSprite() = 0;
    virtual const class Program& GetProgram() const;
    virtual Entity GetRenderableEntity() const = 0;
};

enum class EntityType
{
    Back,
    Tile,
    Character,
    UI,
    Common,
};

class RenderableEntity
    : public Renderable
    , public Entity
{
public:
    RenderableEntity(EntityType type, const Sprite& sprite, Pos pos, Size size = Size{ 1 });
    EntityType GetType() const;

protected:
    // Renderable
    Sprite& GetSprite() override;
    Entity GetRenderableEntity() const override;

private:
    Sprite m_sprite;
    const EntityType m_type;
};
