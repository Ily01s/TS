// src/Vertex.cpp
#include "Vertex.h"

Vertex::Vertex(float _x, float _y, float _z, int _id) : x(_x), y(_y), z(_z), id(_id) {}

float Vertex::getX() const { return x; }
float Vertex::getY() const { return y; }
float Vertex::getZ() const { return z; }
int Vertex::getId() const { return id; }

