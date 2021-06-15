#include <iostream>
#include "Distribution/distribution.h"
int main()
{
    distribution test_distribution(true);
    test_distribution.show();
    float n_cost = test_distribution.cost();
    char answer = 'y';
    while (answer == 'y')
    {
        test_distribution.optimize();
        std::cin.clear();
        std::cout << "would you like to optimize again?[y/n]: ";
        std::cin >> answer;
    }
}