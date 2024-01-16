// src/Graph.cpp
#include "Graph.h"

void Graph::addEdge(const Vertex& src, const Vertex& dest, float weight) {
    adjList[src.getId()].emplace_back(dest.getId(), weight);
    adjList[dest.getId()].emplace_back(src.getId(), weight);
}

const Graph::AdjList& Graph::getNeighbors(int vertexId) const {
    static const AdjList emptyList;
    auto it = adjList.find(vertexId);
    if (it != adjList.end()) {
        return it->second;
    }
    return emptyList;
}

const std::unordered_map<int, Graph::AdjList>& Graph::getAdjacencyList() const {
    return adjList;
}

