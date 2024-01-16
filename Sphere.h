#ifndef SPHERE_H
#define SPHERE_H

#include <GL/gl.h>
#include <cmath>
#include "Vertex.h"

class Sphere
{
    public:
        Sphere(const Vertex& center, float radius);
        virtual ~Sphere();
        void setPosition(const Vertex& newCenter);
        Vertex getPosition() const;
        void drawSphere(double r, int lats, int longs);

    protected:

    private:
        Vertex center;
        float radius=1.5;
};

#endif // SPHERE_H
