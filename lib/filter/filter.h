#ifndef FILTER_H
#define FILTER_H

class Filter
{
private:
    float _weight;
    float _filterData = 0;

public:
    Filter(int weight);
    int setWeight(int weight);
    int getWeight();
    int filter(int value);
};

#endif // !FILTER_H