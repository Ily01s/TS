// include/Triangle.h
#pragma once
#include "Vertex.h"

class Triangle {
public:
    // Constructeur prenant trois objets Vertex pour définir les sommets du triangle
    Triangle(const Vertex& v1, const Vertex& v2, const Vertex& v3);

    // Accéder aux sommets du triangle
    const Vertex& getVertex1() const;
    const Vertex& getVertex2() const;
    const Vertex& getVertex3() const;

private:
    Vertex vertex1, vertex2, vertex3;  // Sommets du triangle
};
