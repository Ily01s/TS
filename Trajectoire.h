// include/Trajctoire.h
#pragma once
#include <vector>
#include "Vertex.h"
#include "Mesh.h"
#include <unordered_map>
#include <algorithm>

class Trajectoire {
public:
    Trajectoire();
    ~Trajectoire();

    void addPoint(const Vertex& point);
    float calculateLength() const;
    void visualize() const;

    void generateTrajectoryDijkstra(const Mesh& mesh, int startVertexId, int endVertexId);



private:
    std::vector<Vertex> points;  // Points de la trajectoire
};
