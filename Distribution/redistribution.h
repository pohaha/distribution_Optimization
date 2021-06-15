#pragma once
#include "cell.h"
struct redistribution
{
    cell m_mainCell;
    cell m_submissiveCell;
    cell m_cellInLine;
    cell m_cellInColumn;
    float m_influence = 0;
    void show();
    redistribution(cell n_mainCell,
                   cell n_submissiceCell,
                   cell n_cellInLine,
                   cell n_cellInColumn);
    redistribution();
};
