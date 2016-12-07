//
// Created by mark on 28/09/16.
//

#include "Newtonian.h"

Newtonian::Newtonian(double gravity) {
    m_gravity = gravity;
}

void Newtonian::applyPhysics(Particle *theParticle, double time) {

    double newX, newY, newZ;
    double newXVelocity, newYVelocity, newZVelocity;

    // Get current particle position
    std::tuple<double, double, double> currentPos = theParticle->getPos();
    newX = std::get<0>(currentPos);
    newY = std::get<1>(currentPos);
    newZ = std::get<2>(currentPos);

    // Get current particle velocity
    std::tuple<double, double, double> currentVelocity = theParticle->getVelocity();
    newXVelocity = std::get<0>(currentVelocity);
    newYVelocity = std::get<1>(currentVelocity);
    newZVelocity = std::get<2>(currentVelocity);

    // Set previous velocity
    theParticle->setPrevVelocity(currentVelocity);

    // Calculate new y velocity after gravity
    newYVelocity += m_gravity / 10000 * time;

    // Update velocities (unused for this Physics model but used if switched)
    theParticle->setVelocity(newXVelocity, newYVelocity, newZVelocity);

    // Save new values
    theParticle->setPos(newX + newXVelocity, newY + newYVelocity, newZ + newZVelocity);
}

std::string Newtonian::getName() {
    return "Newtonian";
}

// Menu functions
int Newtonian::getNumEditableParameters() {
    return 1;
}

void Newtonian::setParameter(int index, double value) {
    if (index == 0) {
        setGravity(value);
    }
}

std::pair<std::string, double> Newtonian::getParameter(int index) {
    if (index == 0) {
        return std::make_pair("Gravity", getGravity());
    }
}

void Newtonian::resetParameters() {
    m_gravity = -9.81;
}

// Getters
double Newtonian::getGravity() {
    return m_gravity;
}

// Setters
void Newtonian::setGravity(double gravity) {
    m_gravity = gravity;
}