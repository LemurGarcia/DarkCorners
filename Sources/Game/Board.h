#pragma once

#include "Entity.h"
#include <memory>

class Board
{
public:
    Board();
    void Render();

private:
    std::unique_ptr<RenderableEntity>               m_back;
    std::unique_ptr<RenderableEntity>               m_board_back;
    std::vector<std::unique_ptr<RenderableEntity>>  m_cells;

    float m_board_padding = 0.05f;

    Entity m_camera;
};