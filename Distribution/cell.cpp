#include "cell.h"
#include <iostream>

cell::cell(unsigned int n_ProviderId,
           unsigned int n_consumerId) : m_consumerId(n_consumerId),
                                        m_providerId(n_ProviderId)
{
    std::cout << "cell id: ["
              << m_providerId
              << "]["
              << m_consumerId
              << "]"
              << std::endl;
    std::cout << "input the transfer_cost: ";
    std::cin >> m_transferCost;
    std::cout << "this cell is in current solution?[0/1]: ";
    std::cin >> m_inSolution;
    if (m_inSolution)
    {
        std::cout << "input the amount of transferred items: ";
        std::cin >> m_transfer_amount;
    }
}

cell::~cell()
{
}
cell::cell()
{
}
void cell::changeAmount(int volume)
{
    m_transfer_amount += volume;
    if (m_transfer_amount == 0)
        m_inSolution = false;
    else if (m_transfer_amount < 0)
        std::cout << "ERROR!" << std::endl;
    else
        m_inSolution = true;
}
void cell::show(bool inLine)
{
    std::cout << "cell"
              << "[" << m_providerId << "]"
              << "[" << m_consumerId << "]: "
              << m_transferCost
              << "(" << m_transfer_amount << ")";
    if (not inLine)
        std::cout << std::endl;
}