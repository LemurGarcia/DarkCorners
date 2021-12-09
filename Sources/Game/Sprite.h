
#pragma once

#include <Engine/Texture.h>
#include <Engine/Shader.h>

#define WIDTH_IN_TILES         8
#define HEIGHT_IN_TILES        8

#define DEFINE_CLASS(name) class name : public glm::vec2    \
{                                                           \
public:                                                     \
    using glm::vec2::vec2;                                  \
};

DEFINE_CLASS(Vel);
DEFINE_CLASS(Pos);
DEFINE_CLASS(Size);

struct PosOnBoard
{
    uint16_t x = 0;
    uint16_t y = 0;
    PosOnBoard(uint16_t _x, uint16_t _y)
    {
        x = _x;
        y = _y;
    }

    bool operator==(PosOnBoard pos) const
    {
        return (x == pos.x && y == pos.y);
    }
    bool operator <(PosOnBoard pos) const
    {
        return y == pos.y ? x < pos.x : y < pos.y;
    }
};

enum class BlendMode
{
    NoBlend,
    Alpha,
    Add,
};

class Sprite
{
public:
    Sprite(const Sprite&) = default;
    Sprite(const Texture& tex, BlendMode blending, bool is_isometric = false);
    void Render(const Program& prog, const class Entity& entity, const class Entity& camera);
    void Render(const Program& prog, Pos pos, Size size);

    const Texture& GetTexture() const;

private:
    const Texture& m_tex;
    const BlendMode m_blending;
    const bool m_isometric;
};
