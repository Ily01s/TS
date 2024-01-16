// src/Triangle.cpp
#include "Triangle.h"

Triangle::Triangle(const Vertex& v1, const Vertex& v2, const Vertex& v3)
    : vertex1(v1), vertex2(v2), vertex3(v3) {
    // Initialisation, si nécessaire
}

const Vertex& Triangle::getVertex1() const {
    return vertex1;
}

const Vertex& Triangle::getVertex2() const {
    return vertex2;
}

const Vertex& Triangle::getVertex3() const {
    return vertex3;
}
