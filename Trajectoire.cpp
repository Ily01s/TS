// include/Trajctoire.cpp
#include "Trajectoire.h"
#include <iostream>
#include <cmath>
#include <queue>
#include <limits>

Trajectoire::Trajectoire() {
    // Initialisation, si nécessaire
}

Trajectoire::~Trajectoire() {
    // Nettoyage, si nécessaire
}

void Trajectoire::addPoint(const Vertex& point) {
    points.push_back(point);
}

float Trajectoire::calculateLength() const {
    float length = 0.0f;
    for (size_t i = 1; i < points.size(); ++i) {
        float dx = points[i].getX() - points[i - 1].getX();
        float dy = points[i].getY() - points[i - 1].getY();
        float dz = points[i].getZ() - points[i - 1].getZ();
        length += std::sqrt(dx * dx + dy * dy + dz * dz);
    }
    return length;
}

void Trajectoire::visualize() const {
    std::cout << "Trajectory Visualization:" << std::endl;
    for (const Vertex& point : points) {
        std::cout << "Point (" << point.getX() << ", " << point.getY() << ", " << point.getZ() << ")" << std::endl;
    }
    std::cout << "Total Length: " << calculateLength() << std::endl;
}

struct GraphVertex {
    int id;
    float cost;
    GraphVertex(int id, float cost) : id(id), cost(cost) {}
};

struct Compare {
    bool operator()(const GraphVertex& a, const GraphVertex& b) const {
        return a.cost > b.cost;
    }
};

std::vector<int> dijkstra(const Graph& graph, int startVertex, int endVertex) {
    std::priority_queue<GraphVertex, std::vector<GraphVertex>, Compare> pq;
    std::unordered_map<int, float> distances;
    std::unordered_map<int, int> previous;

    for (const auto& pair : graph.getAdjacencyList()) {
        distances[pair.first] = std::numeric_limits<float>::infinity();
    }

    distances[startVertex] = 0;
    pq.push(GraphVertex(startVertex, 0));

    while (!pq.empty()) {
        GraphVertex currentVertex = pq.top();
        pq.pop();

        if (currentVertex.id == endVertex) {
            break;
        }

        for (const auto& edge : graph.getNeighbors(currentVertex.id)) {
            int neighborId = edge.first;
            float weight = edge.second;
            float distanceThroughU = distances[currentVertex.id] + weight;

           if (distanceThroughU < distances[neighborId]) {
                distances[neighborId] = distanceThroughU;
                previous[neighborId] = currentVertex.id;
                pq.push(GraphVertex(neighborId, distanceThroughU));
            }
        }
    }

    std::vector<int> path;
    for (int at = endVertex; at != startVertex; at = previous[at]) {
        path.push_back(at);
    }
    path.push_back(startVertex);
    std::reverse(path.begin(), path.end());

    return path;
}

void Trajectoire::generateTrajectoryDijkstra(const Mesh& mesh, int startVertexId, int endVertexId) {
    const auto& graph = mesh.getGraph();
    std::vector<int> vertexPath = dijkstra(graph, startVertexId, endVertexId);
    points.clear();

    for (int vertexId : vertexPath) {
        Vertex v = mesh.getVertexById(vertexId);
        addPoint(v);
    }
}
