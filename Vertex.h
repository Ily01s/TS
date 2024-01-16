// include/Vertex.h
#pragma once

class Vertex {
public:
    Vertex(float _x, float _y, float _z, int _id);

    float getX() const;
    float getY() const;
    float getZ() const;
    int getId() const;

private:
    float x, y, z;
    int id;  // Identifiant unique pour le vertex
};

