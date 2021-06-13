#pragma once
#include <string>
class cell
{
private:
    float m_transferCost = 0;
    std::string consumer = "unknown";
    std::string provider = "unknown";

public:
    cell(/* args */);
    ~cell();
};
