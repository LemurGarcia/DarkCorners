#include "Board.h"

#include <Engine/ResourceManager.h>

Board::Board()
    : m_camera(Pos(0), Size(1.0f))
{
    m_back = std::make_unique<RenderableEntity>(
        EntityType::Back,
        Sprite(ResourceManager::GetTexture("Images/back.png", Texture::WrapMode::Clamp), BlendMode::Alpha),
        Pos(0), Size(2, 1));

    float board_back_size = 0.9f;

    m_board_back = std::make_unique<RenderableEntity>(
        EntityType::Back,
        Sprite(ResourceManager::GetTexture("Images/board_back.png", Texture::WrapMode::Clamp), BlendMode::Alpha),
        Pos(0), Size(board_back_size));

    float m_tile_size = (board_back_size - m_board_padding * 2) / WIDTH_IN_TILES;
    float start = 0.1f - board_back_size / 2.f;
    std::string cell_name;

    for (int i = 0; i < HEIGHT_IN_TILES; i++)
    {
        for (int j = 0; j < WIDTH_IN_TILES; j++)
        {
            cell_name = (i + j) % 2 == 1 ? "Images/yellow_cell.png" : "Images/brown_cell.png";
            m_cells.push_back(std::make_unique<RenderableEntity>(
                    EntityType::Tile,
                    Sprite(ResourceManager::GetTexture(cell_name, Texture::WrapMode::Clamp), BlendMode::Alpha),
                    Pos(start + i * m_tile_size, start + j * m_tile_size), Size(m_tile_size)));
        }
    }
}

void Board::Render()
{
    m_back->Render(m_camera);
    m_board_back->Render(m_camera);

    for (auto& cell : m_cells)
        cell->Render(m_camera);
}
