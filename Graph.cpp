// src/Graph.cpp
#include "Graph.h"
#include <algorithm>
void Graph::addEdge(const Vertex& src, const Vertex& dest, float weight) {
    // V�rifier si l'ar�te existe d�j� avant de l'ajouter
    if (std::find_if(adjList[src.getId()].begin(), adjList[src.getId()].end(),
        [&dest](const std::pair<int, float>& p) { return p.first == dest.getId(); }) == adjList[src.getId()].end()) {
        adjList[src.getId()].emplace_back(dest.getId(), weight);
    }

    // M�me v�rification pour l'ar�te dans l'autre sens
    if (std::find_if(adjList[dest.getId()].begin(), adjList[dest.getId()].end(),
        [&src](const std::pair<int, float>& p) { return p.first == src.getId(); }) == adjList[dest.getId()].end()) {
        adjList[dest.getId()].emplace_back(src.getId(), weight);
    }
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

