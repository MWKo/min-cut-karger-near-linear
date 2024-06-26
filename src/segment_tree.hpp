#pragma once

#include <vector>
#include "types.hpp"

class SegmentTree {
public:
    typedef EdgeWeight DataType;

private:
    size_t mListSize;
    std::vector<DataType> mValues;
    std::vector<DataType> mLazy;

    void initTree(const DataType* list, size_t left, size_t right, size_t valuesIndex);
    void updateLazy(size_t valuesIndex, size_t left, size_t right);
    void addToIntervalRecursive(DataType value2add, size_t intervalStart, size_t intervalEnd, size_t left, size_t right, size_t valuesIndex);

public:
    explicit SegmentTree(size_t listSize);
    SegmentTree(const DataType* list, size_t listSize);

    size_t listSize() const { return mListSize; }
    DataType minValue() const { return mValues[0]; }
    size_t minIndex();

    void intervalAdd(DataType value, size_t intervalStart, size_t intervalEnd);
};