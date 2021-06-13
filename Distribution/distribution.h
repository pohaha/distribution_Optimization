#pragma once
#include <string>
#include "cell.h"

class distribution
{
private:
    unsigned int m_amountOfComsumers = 0;
    unsigned int m_amountOfProviders = 0;
    std::string *m_consumers = nullptr;
    std::string *m_providers = nullptr;
    cell *m_grid = nullptr;

public:
    distribution(const bool &construct = false);
    ~distribution();
};
