#ifndef CUBE_H
#define CUBE_H

#pragma once
#include <array>
#include <vector>
#include "Triangle.h"
#include "Vertex.h"
#include "Mesh.h"

class Cube
{
    public:
        Cube();
        virtual ~Cube();
        // Définition d'une paire de triangles pour représenter une face
            using Face = std::pair<Triangle, Triangle>;
    void buildCube(Mesh& mesh,float sideLength);  // Méthode pour construire le cube
    const std::vector<Face>& getFaces() const;

    protected:

    private:
        Mesh mesh;
        std::vector<Face> faces;

};

#endif // CUBE_H
