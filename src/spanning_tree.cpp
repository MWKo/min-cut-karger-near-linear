#include "spanning_tree.hpp"

#include <vector>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include "union_find.hpp"

template <bool MAX_SPANNING_TREE, bool USE_WEIGHTS>
static std::vector<size_t> spanningTree(const MultiGraph& graph, const EdgeWeight* weights, size_t numWeights) {
    if (graph.numVertices() <= 1) {
        return std::vector<size_t>();
    }

    std::vector<size_t> edgeIndices;
    edgeIndices.reserve(graph.numVertices() - 1);

    const std::vector<MultiEdge>& edges = graph.edges();
    const std::vector<MultiEdge>* edgesPtr = &edges;

    if constexpr(USE_WEIGHTS) {
        if (edges.size() != numWeights) {
            throw std::runtime_error("the number of edges of the graph does not match the number of weights");
        }
    }

    std::vector<size_t> sortedIndices(edges.size());
    std::iota(sortedIndices.begin(), sortedIndices.end(), 0);

    if constexpr(USE_WEIGHTS && MAX_SPANNING_TREE) {
        std::sort(sortedIndices.begin(), sortedIndices.end(), [weights](size_t i0, size_t i1) {
            return weights[i0] > weights[i1];
        });
    }
    if constexpr(USE_WEIGHTS && !MAX_SPANNING_TREE) {
        std::sort(sortedIndices.begin(), sortedIndices.end(), [weights](size_t i0, size_t i1) {
            return weights[i0] < weights[i1];
        });
    }
    if constexpr(!USE_WEIGHTS && MAX_SPANNING_TREE) {
        std::sort(sortedIndices.begin(), sortedIndices.end(), [edgesPtr](size_t i0, size_t i1) {
            return (*edgesPtr)[i0].multiplicity() > (*edgesPtr)[i1].multiplicity();
        });
    }
    if constexpr(!USE_WEIGHTS && !MAX_SPANNING_TREE) {
        std::sort(sortedIndices.begin(), sortedIndices.end(), [edgesPtr](size_t i0, size_t i1) {
            return (*edgesPtr)[i0].multiplicity() < (*edgesPtr)[i1].multiplicity();
        });
    }

    UnionFind uf(graph.numVertices());
    for (size_t index : sortedIndices) {
        const MultiEdge& edge = edges[index];

        if (uf.find(edge.endpoint(0)) != uf.find(edge.endpoint(1))) {
            edgeIndices.push_back(index);

            if (edgeIndices.size() == graph.numVertices() - 1) {
                return edgeIndices;
            }

            uf.unionSets(edge.endpoint(0), edge.endpoint(1));
        }
    }

    throw std::runtime_error("spanningTree: the graph is not connected");
} 

std::vector<size_t> minSpanningTree(const MultiGraph& graph) {
    return spanningTree<false, false>(graph, nullptr, 0);
}

std::vector<size_t> minSpanningTree(const MultiGraph& graph, const EdgeWeight* weights, size_t numWeights) {
    return spanningTree<false, true>(graph, weights, numWeights);
}

std::vector<size_t> maxSpanningTree(const MultiGraph& graph) {
    return spanningTree<true, false>(graph, nullptr, 0);
}

std::vector<size_t> maxSpanningTree(const MultiGraph& graph, const EdgeWeight* weights, size_t numWeights) {
    return spanningTree<true, true>(graph, weights, numWeights);
}
