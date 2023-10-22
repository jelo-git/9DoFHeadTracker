#include "filter.h"

Filter::Filter(int weight)
{
    _weight = weight;
}
int Filter::getWeight()
{
    return _weight;
}
int Filter::setWeight(int weight)
{
    if (weight < 0 || weight > 1)
    {
        return 1; // ERR
    }
    _weight = weight;
    return 0; // OK
}
int Filter::filter(int value)
{
    _filterData = (1 - _weight) * _filterData + _weight * (float)value;
    return _filterData;
}