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

    Entity m_camera;
};