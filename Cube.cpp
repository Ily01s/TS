#include "Cube.h"
#include <cmath>



Cube::Cube(){
}
Cube::~Cube(){}
void Cube::buildCube(float sideLength) {
    float halfSide = sideLength / 2;

    // Définir les 8 sommets du cube
    Vertex v1(-halfSide, -halfSide, halfSide,1);   // Sommet 1
    Vertex v2(halfSide, -halfSide, halfSide,2);    // Sommet 2
    Vertex v3(halfSide, halfSide, halfSide,3);     // Sommet 3
    Vertex v4(-halfSide, halfSide, halfSide,4);    // Sommet 4
    Vertex v5(-halfSide, -halfSide, -halfSide,5);  // Sommet 5
    Vertex v6(halfSide, -halfSide, -halfSide,6);   // Sommet 6
    Vertex v7(halfSide, halfSide, -halfSide,7);    // Sommet 7
    Vertex v8(-halfSide, halfSide, -halfSide,8);   // Sommet 8

    // Construire les 12 triangles (2 par face)
    faces.push_back({Triangle(v1, v2, v3), Triangle(v3, v4, v1)}); // Face avant
    faces.push_back({Triangle(v5, v8, v7), Triangle(v7, v6, v5)}); // Face arrière
    faces.push_back({Triangle(v4, v3, v7), Triangle(v7, v8, v4)}); // Face supérieure
    faces.push_back({Triangle(v1, v5, v6), Triangle(v6, v2, v1)}); // Face inférieure
    faces.push_back({Triangle(v2, v6, v7), Triangle(v7, v3, v2)}); // Face droite
    faces.push_back({Triangle(v1, v4, v8), Triangle(v8, v5, v1)}); // Face gauche
}


const std::vector<Cube::Face>& Cube::getFaces() const{
    return faces;
}
