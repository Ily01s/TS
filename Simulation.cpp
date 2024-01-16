// include/Simulation.cpp
#include "Simulation.h"

#include <iostream>

Simulation::Simulation() : mesh(), trajectoire() {
    // Initialisation des autres membres, si nécessaire.
}

void Simulation::initialize() {
    // Initialiser le maillage, la trajectoire, etc.
}

void Simulation::runAlgorithm() {
    int startVertexId = 1; // ID du sommet de départ
    int endVertexId = 4;   // ID du sommet d'arrivée

    trajectoire.generateTrajectoryDijkstra(mesh, startVertexId, endVertexId);
}

void Simulation::updateDisplay() {
    trajectoire.visualize();
}

Trajectoire& Simulation::getTrajectoire() {
    return trajectoire;
}
