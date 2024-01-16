// include/Simulation.h
#pragma once
#include "Mesh.h"
#include "Trajectoire.h"

class Simulation {
public:
    Simulation();
    
    void initialize();
    void runAlgorithm(); // Méthode pour exécuter l'algorithme de trajectoire
    void updateDisplay(); // Mettre à jour l'affichage OpenGL
    Trajectoire& getTrajectoire(); // Retourne une référence à Trajectoire

private:
    Mesh mesh;               // Maillage de la surface
    Trajectoire trajectoire;
};
