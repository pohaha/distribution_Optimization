#include "distribution.h"
#include <iostream>
#include <vector>
#include "redistribution.h"
distribution::distribution(const bool &construct)
{
    if (construct)
    {
        std::cout << "input the amount of providers: ";
        std::cin >> m_amountOfProviders;
        m_providers = new int[m_amountOfProviders];
        for (unsigned int i = 0; i < m_amountOfProviders; i++)
        {
            std::cout << "Input the amount provided by #" << i << ": ";
            std::cin >> m_providers[i];
        }
        std::cout << "input the amount of consumers: ";
        std::cin >> m_amountOfConsumers;
        m_consumers = new int[m_amountOfConsumers];
        for (unsigned int i = 0; i < m_amountOfConsumers; i++)
        {
            std::cout << "Input the amount consumed by #" << i << ": ";
            std::cin >> m_consumers[i];
        }
        m_grid = new cell *[m_amountOfProviders];
        for (unsigned int i = 0; i < m_amountOfProviders; i++)
        {
            m_grid[i] = new cell[m_amountOfConsumers];
            for (unsigned int j = 0; j < m_amountOfConsumers; j++)
                m_grid[i][j] = cell(i, j);
        }
    }
    std::cout << "empty distribution" << std::endl;
}

distribution::~distribution()
{
    delete[] m_consumers;
    for (unsigned int i = 0; i < m_amountOfProviders; i++)
        delete[] m_grid[i];
    delete[] m_grid;
    delete[] m_providers;
}
float distribution::cost()
{
    float rt_cost = 0;
    for (unsigned int i = 0; i < m_amountOfProviders; i++)
    {
        for (unsigned int j = 0; j < m_amountOfConsumers; j++)
        {
            if (m_grid[i][j].m_inSolution)
                rt_cost += (m_grid[i][j].m_transferCost) * (m_grid[i][j].m_transfer_amount);
        }
    }
    std::cout << "total cost of that solution is: " << rt_cost << std::endl;
    return rt_cost;
}
void distribution::show()
{
    std::cout << "\t";
    for (unsigned int i = 0; i < m_amountOfConsumers; i++)
        std::cout << i << "\t";
    std::cout << "\n";
    for (unsigned int i = 0; i < m_amountOfProviders; i++)
    {
        for (unsigned int j = 0; j < (m_amountOfConsumers + 2); j++)
        {
            if (j == 0)
                std::cout << i << "\t";
            else if (j <= m_amountOfConsumers)
            {
                if (m_grid[i][j - 1].m_inSolution)
                {
                    std::cout << m_grid[i][j - 1].m_transferCost
                              << "("
                              << m_grid[i][j - 1].m_transfer_amount
                              << ")\t";
                }
                else
                    std::cout << m_grid[i][j - 1].m_transferCost << "(0)\t";
            }
            else
                std::cout << "| " << m_providers[i] << "\n";
        }
    }
    for (unsigned int i = 0; i < ((m_amountOfConsumers + 1) * 8); i++)
        std::cout << "-";
    std::cout << std::endl;
    std::cout << "\t";

    for (unsigned int i = 0; i < m_amountOfConsumers; i++)
        std::cout << m_consumers[i] << "\t";
    std::cout << std::endl;
}
void distribution::redistribute(redistribution n_redistribution)
{
    int inLineVolume = n_redistribution.m_cellInLine.m_transfer_amount;
    int inColumnVolume = n_redistribution.m_cellInColumn.m_transfer_amount;
    int redistributedVolume = (inLineVolume < inColumnVolume) ? (inLineVolume) : (inColumnVolume);
    unsigned int mainRow = n_redistribution.m_mainCell.m_providerId;
    unsigned int mainColumn = n_redistribution.m_mainCell.m_consumerId;
    unsigned int subRow = n_redistribution.m_submissiveCell.m_providerId;
    unsigned int subColumn = n_redistribution.m_submissiveCell.m_consumerId;
    m_grid[mainRow][mainColumn].changeAmount(redistributedVolume);
    m_grid[subRow][mainColumn].changeAmount((redistributedVolume * (-1)));
    m_grid[mainRow][subColumn].changeAmount((redistributedVolume * (-1)));
    m_grid[subRow][subColumn].changeAmount(redistributedVolume);
}
void distribution::optimize()
{
    std::vector<redistribution> eligible_redistributions;
    for (unsigned int i = 0; i < m_amountOfProviders; i++)
    {
        for (unsigned int j = 0; j < m_amountOfConsumers; j++)
        {

            if (not m_grid[i][j].m_inSolution)
            {
                for (unsigned int rowCounter = 0; rowCounter < m_amountOfProviders; rowCounter++)
                {
                    if ((rowCounter != i) and (m_grid[rowCounter][j].m_inSolution))
                    {
                        for (unsigned int columnCounter = 0; columnCounter < m_amountOfConsumers; columnCounter++)
                        {
                            if ((columnCounter != j) and (m_grid[i][columnCounter].m_inSolution))
                            {
                                eligible_redistributions.push_back(redistribution(m_grid[i][j],
                                                                                  m_grid[rowCounter][columnCounter],
                                                                                  m_grid[rowCounter][j],
                                                                                  m_grid[i][columnCounter]));
                            }
                        }
                    }
                }
            }
        }
    }
    redistribution bestRedistribution;
    bool exists = false;
    for (auto element : eligible_redistributions)
        if (not exists)
        {
            if (element.m_influence <= 0)
            {
                bestRedistribution = element;
                exists = true;
            }
        }
        else
        {
            if (element.m_influence < bestRedistribution.m_influence)
                bestRedistribution = element;
        }
    if (not exists)
    {
        std::cout << "there are no negative or zero redistributions. nothing to redistribute!" << std::endl;
        return;
    }
    std::cout << "best singular redistribotion is: " << std::endl;
    bestRedistribution.show();
    redistribute(bestRedistribution);
    show();
}