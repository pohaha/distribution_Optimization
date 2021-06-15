#pragma once
#include <string>
class cell
{
private:
    float m_transferCost = 0;
    unsigned int m_consumerId = 0;
    unsigned int m_providerId = 0;
    int m_transfer_amount = 0;
    bool m_inSolution = false;
    friend class distribution;
    friend class redistribution;

public:
    cell();
    cell(unsigned int n_ProviderId, unsigned int n_consumerId);
    ~cell();
    void show(bool inLine = false);
    void changeAmount(int n_amount);
};
