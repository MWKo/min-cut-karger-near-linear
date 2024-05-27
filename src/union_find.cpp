#include "union_find.hpp"
#include <numeric>

UnionFind::UnionFind(dtype n) : mParents(n), mHeight(n, 0) {
    std::iota(mParents.begin(), mParents.end(), 0);
}

UnionFind::dtype UnionFind::find(dtype x) const {   
    dtype parent = mParents[x];
    while (parent != x) {
        x = parent;
        parent = mParents[x];
    }
    return x;
}

UnionFind::dtype UnionFind::unionSets(dtype x, dtype y) {
    dtype repX = find(x);
    dtype repY = find(y);

    if (repX == repY) return repX;
    
    htype hX = mHeight[repX];
    htype hY = mHeight[repY];

    // Add smaller tree to larger tree to keep the height small

    if (hX > hY) {
        mParents[repY] = repX;
        return repX;
    }

    if (hX < hY) {
        mParents[repX] = repY;
        return repY;
    }

    mParents[repY] = repX;
    mHeight[repX]++;
    return repX;
}
