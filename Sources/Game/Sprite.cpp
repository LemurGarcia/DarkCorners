
#include "Sprite.h"
#include "Entity.h"
#include <Engine/Engine.h>
#include <Engine/VertexBuffer.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_transform_2d.hpp>

Sprite::Sprite(const Texture& tex, BlendMode blending, bool is_isometric)
    : m_tex(tex)
    , m_blending(blending)
    , m_isometric(is_isometric)
{}

void Sprite::Render(const Program& prog, const Entity& entity, const Entity& camera)
{
    Size entity_size
        = Size(entity)
        * Size((float)m_tex.GetWidth() / m_tex.GetHeight(), 1.0f);

    Size camera_size
        = Size(camera)
        * Size((float)Engine::GetHeight() / Engine::GetWidth(), 1.0f);

    glm::mat3 mat_pos = glm::scale(glm::rotate(glm::translate(glm::mat3(1), (Pos)entity * 2.0f), entity.GetAngle()), entity_size);
    glm::mat3 mat_camera = glm::translate(glm::rotate(glm::scale(glm::mat3(1), camera_size), camera.GetAngle()), (Pos)camera * (-2.0f));
    glm::mat3 mat = mat_camera * mat_pos;
    if (m_isometric)
        mat = glm::shearY(glm::mat3(1), 0.15f) * mat;

    ProgramGuard program_guard(prog);
    prog.SetTexture("tex", m_tex, 0);
    prog.SetUniform("mat_tex", glm::mat3(1));
    prog.SetUniform("mat_pos", mat);

    if (m_blending != BlendMode::NoBlend)
    {
        glEnable(GL_BLEND);
        switch (m_blending)
        {
        case BlendMode::Alpha:
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            break;
        case BlendMode::Add:
            glBlendFunc(GL_ONE, GL_ONE);
            break;
        }
    }

    VertexBuffer::FullScreenQuad().DrawElements();

    if (m_blending != BlendMode::NoBlend)
        glDisable(GL_BLEND);
}

void Sprite::Render(const Program& prog, Pos pos, Size size)
{
    Render(prog, Entity(pos, size), Entity(Pos(0), Size(1)));
}

const Texture& Sprite::GetTexture() const
{
    return m_tex;
}
