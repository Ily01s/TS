// src/Mesh.cpp
#include "Mesh.h"

Mesh::Mesh() {
    // Initialisation du maillage, si nécessaire
}

Mesh::~Mesh() {
    // Nettoyage des ressources, si nécessaire
}

void Mesh::addTriangle(const Triangle& triangle) {
    triangles.push_back(triangle);
}

const std::vector<Triangle>& Mesh::getTriangles() const {
    return triangles;
}

void Mesh::buildGraph() {
    for (const auto& triangle : triangles) {
        // Récupérer les sommets du triangle
        const Vertex& v1 = triangle.getVertex1();
        const Vertex& v2 = triangle.getVertex2();
        const Vertex& v3 = triangle.getVertex3();

        // Calculer les poids (distances euclidiennes) pour chaque arête
        float weight_v1_v2 = std::sqrt(std::pow(v1.getX() - v2.getX(), 2) +
                                       std::pow(v1.getY() - v2.getY(), 2) +
                                       std::pow(v1.getZ() - v2.getZ(), 2));

        float weight_v2_v3 = std::sqrt(std::pow(v2.getX() - v3.getX(), 2) +
                                       std::pow(v2.getY() - v3.getY(), 2) +
                                       std::pow(v2.getZ() - v3.getZ(), 2));

        float weight_v3_v1 = std::sqrt(std::pow(v3.getX() - v1.getX(), 2) +
                                       std::pow(v3.getY() - v1.getY(), 2) +
                                       std::pow(v3.getZ() - v1.getZ(), 2));

        // Ajouter les arêtes au graphe
        graph.addEdge(v1, v2, weight_v1_v2);
        graph.addEdge(v2, v3, weight_v2_v3);
        graph.addEdge(v3, v1, weight_v3_v1);
    }
    //std::cout << "graphe bien construit!! ";
}


/*const Graph& Mesh::getGraph() const {
    return graph;
}*/

Vertex Mesh::getVertexById(int id) const {
    auto it = vertices.find(id);
    if (it != vertices.end()) {
        return it->second;
    }


    return Vertex(0, 0, 0,0);
}


const Graph& Mesh::getGraph() const {
    return graph;
}
