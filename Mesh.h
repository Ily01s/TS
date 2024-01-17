// include/Mesh.h
#pragma once
#include <vector>
#include "Triangle.h"
#include "Graph.h"
#include <cmath>
#include <iostream>

class Mesh {
public:
    Mesh();
    ~Mesh();

    void buildGraph();
     const Graph& getGraph() const;
    void addTriangle(const Triangle& triangle);
    const std::vector<Triangle>& getTriangles() const;
    Vertex getVertexById(int id) const;

private:
    std::vector<Triangle> triangles;
    Graph graph;
    std::unordered_map<int, Vertex> vertices;
    /*std::unordered_map<int, AdjList> graph;*/
};
