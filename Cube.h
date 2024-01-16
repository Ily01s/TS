#ifndef CUBE_H
#define CUBE_H

#pragma once
#include <array>
#include <vector>
#include "Triangle.h"
#include "Vertex.h"

class Cube
{
    public:
        Cube();
        virtual ~Cube();
        // D�finition d'une paire de triangles pour repr�senter une face
            using Face = std::pair<Triangle, Triangle>;
    void buildCube(float sideLength);  // M�thode pour construire le cube
    const std::vector<Face>& getFaces() const;

    protected:

    private:

        std::vector<Face> faces;

};

#endif // CUBE_H
