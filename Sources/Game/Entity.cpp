
#include "Entity.h"
#include "Sprite.h"

Entity::Entity(Pos pos, Size size)
    : m_pos(pos)
    , m_size(size)
{}

bool Entity::IsCollide(const Entity& entity) const
{
    return
        m_pos.x - m_size.x / 2 - entity.m_size.x / 2 < entity.m_pos.x && entity.m_pos.x < m_pos.x + m_size.x / 2 + entity.m_size.x / 2 &&
        m_pos.y - m_size.y / 2 - entity.m_size.y / 2 < entity.m_pos.y && entity.m_pos.y < m_pos.y + m_size.y / 2 + entity.m_size.y / 2;
}

void Entity::Update(uint64_t delta)
{
    float koeff = (float)delta / 16.0f;
    m_pos += m_vel * koeff;
}

float Entity::GetAngle() const
{
    return m_angle;
}

Entity& Entity::operator+=(Pos pos)
{
    m_pos += glm::vec2(pos);
    return *this;
}

Entity& Entity::operator-=(Pos pos)
{
    m_pos -= glm::vec2(pos);
    return *this;
}

Entity& Entity::operator+=(Vel vel)
{
    m_vel += glm::vec2(vel);
    return *this;
}

Entity& Entity::operator-=(Vel vel)
{
    m_vel -= glm::vec2(vel);
    return *this;
}

Entity& Entity::operator+=(float angle)
{
    m_angle += angle;
    return *this;
}

Entity& Entity::operator-=(float angle)
{
    m_angle -= angle;
    return *this;
}

Entity::operator Size() const
{
    return m_size;
}

Entity::operator Pos() const
{
    return m_pos;
}

Entity::operator Vel() const
{
    return m_vel;
}

void Entity::Set(Pos pos)
{
    m_pos = pos;
}

void Entity::Set(Vel vel)
{
    m_vel = vel;
}

void Entity::Set(Size size)
{
    m_size = size;
}

void Entity::Set(float angle)
{
    m_angle = angle;
}

// Renderable

void Renderable::Render(const Entity& camera)
{
    GetSprite().Render(GetProgram(), GetRenderableEntity(), camera);
}

const Program& Renderable::GetProgram() const
{
    return Program::SimpleProgram();
}

// Renderable Entity

RenderableEntity::RenderableEntity(EntityType type, const Sprite& sprite, Pos pos, Size size)
    : Entity(pos, size)
    , m_sprite(sprite)
    , m_type(type)
{}

EntityType RenderableEntity::GetType() const
{
    return m_type;
}

Sprite& RenderableEntity::GetSprite()
{
    return m_sprite;
}

Entity RenderableEntity::GetRenderableEntity() const
{
    return *this;
}
