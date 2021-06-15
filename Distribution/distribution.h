#pragma once
#include <string>
#include "cell.h"
#include "redistribution.h"

class distribution
{
private:
    unsigned int m_amountOfConsumers = 0;
    unsigned int m_amountOfProviders = 0;
    int *m_consumers = nullptr;
    int *m_providers = nullptr;
    cell **m_grid = nullptr;
    void redistribute(redistribution n_redistribution);

public:
    distribution(const bool &construct = false);
    ~distribution();
    float cost();
    void show();
    void optimize();
};
