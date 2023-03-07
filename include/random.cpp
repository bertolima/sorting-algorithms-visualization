#include "random.hpp"

int generateNumber(int start, int range)
{
    return (start + rand() % range);
}