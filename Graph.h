// include/Graph.h
#pragma once
#include <unordered_map>
#include <vector>
#include "Vertex.h"

class Graph {
public:
    using Edge = std::pair<int, float>; // Pair (Vertex ID, Weight)
    using AdjList = std::vector<Edge>;

    void addEdge(const Vertex& src, const Vertex& dest, float weight);
    const AdjList& getNeighbors(int vertexId) const;
    const std::unordered_map<int, AdjList>& getAdjacencyList() const;

private:
    std::unordered_map<int, AdjList> adjList; // Graph representation
};
