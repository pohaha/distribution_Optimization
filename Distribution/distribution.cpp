#include "distribution.h"
#include <iostream>
distribution::distribution(const bool &construct)
{
    std::cout << "successfull creation" << std::endl;
}

distribution::~distribution()
{
    delete[] m_consumers;
    delete[] m_grid;
    delete[] m_providers;
}
