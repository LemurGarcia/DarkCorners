#include "Board.h"

#include <Engine/ResourceManager.h>

Board::Board()
    : m_camera(Pos(0), Size(1.0f))
{
    m_back = std::make_unique<RenderableEntity>(
        EntityType::Back,
        Sprite(ResourceManager::GetTexture("Images/back.png", Texture::WrapMode::Clamp), BlendMode::Alpha),
        Pos(0), Size(2, 1));

    float back_size_w = 0.9f;
    float back_size_h = 0.9f;
    m_board_back = std::make_unique<RenderableEntity>(
        EntityType::Back,
        Sprite(ResourceManager::GetTexture("Images/board_back.png", Texture::WrapMode::Clamp), BlendMode::Alpha),
        Pos(0, 0), Size(back_size_w, back_size_h));
}

void Board::Render()
{
    m_back->Render(m_camera);
    m_board_back->Render(m_camera);
}
