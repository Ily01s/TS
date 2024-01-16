#include "Sphere.h"

Sphere::Sphere(const Vertex& center, float radius)
    : center(center), radius(radius) {}

Sphere::~Sphere()
{
    //dtor
}

Vertex Sphere::getPosition() const {
    return center;
}

void Sphere::setPosition(const Vertex& newCenter) {
    center = newCenter;
}

void Sphere::drawSphere(const Sphere& sphere) {
    glPushMatrix(); // Sauvegarde la matrice actuelle
    glColor3f(0.5f, 0.5f, 0.5f); // Couleur grise
    glTranslatef(sphere.getPosition().getX(), sphere.getPosition().getY(), sphere.getPosition().getZ()); // Positionne la sphère
    // Remplacer par votre fonction de dessin de sphère, par exemple glutSolidSphere si vous utilisez GLUT
    // glutSolidSphere(sphere.getRadius(), 20, 20);
    glPopMatrix(); // Restaure la matrice
}
