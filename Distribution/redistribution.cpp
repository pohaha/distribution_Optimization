#include "redistribution.h"
#include <iostream>
void redistribution::show()
{
    //line 1
    m_mainCell.show(true);
    std::cout << "\t<-------\t";
    m_cellInLine.show(true);
    std::cout << std::endl;
    //line 2
    m_cellInColumn.show(true);
    std::cout << "\t------->\t";
    m_submissiveCell.show();
    std::cout << "singular redistribution resolves in: " << m_influence << std::endl;
}

redistribution::redistribution() {}
redistribution::redistribution(cell n_mainCell,
                               cell n_submissiceCell,
                               cell n_cellInLine,
                               cell n_cellInColumn) : m_mainCell(n_mainCell),
                                                      m_submissiveCell(n_submissiceCell),
                                                      m_cellInLine(n_cellInLine),
                                                      m_cellInColumn(n_cellInColumn)
{
    m_influence = (m_mainCell.m_transferCost + m_submissiveCell.m_transferCost) -
                  (m_cellInColumn.m_transferCost + m_cellInLine.m_transferCost);
}