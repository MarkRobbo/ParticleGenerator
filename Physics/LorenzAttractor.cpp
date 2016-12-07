//
// Created by mark on 28/09/16.
//

#include "LorenzAttractor.h"

// Creates a Lorenz strange attractor
LorenzAttractor::LorenzAttractor(double sigma, double rho, double beta, double t) {
    m_sigma = sigma;
    m_rho = rho;
    m_beta = beta;
    m_t = t;
}

// Applies physics to the given particle
void LorenzAttractor::applyPhysics(Particle* theParticle, double time) {
    double x, y, z;
    double newX, newY, newZ;

    // Current point
    std::tuple<double, double, double> currentPos = theParticle->getPos();
    x = std::get<0>(currentPos);
    y = std::get<1>(currentPos);
    z = std::get<2>(currentPos);

    // Calculate new point
    newX = x + m_t * m_sigma * (y - x);
    newY = y + m_t * (x * (m_rho - z) - y);
    newZ = z + m_t * (x * newY - m_beta * z);

    // Set previous velocity
    theParticle->setPrevVelocity(theParticle->getVelocity());

    // Update velocities (unused for this Physics model but used if switched)
    theParticle->setVelocity(x - newX, y - newY, z - newZ);

    // Save new values
    theParticle->setPos(newX, newY, newZ);
}

std::string LorenzAttractor::getName() {
    return "Lorenz Attractor";
}

// Menu functions
int LorenzAttractor::getNumEditableParameters() {
    return 4;
}

void LorenzAttractor::setParameter(int index, double value) {
    switch (index) {
        case 0:
            setSigma(value);
            break;
        case 1:
            setRho(value);
            break;
        case 2:
            setBeta(value);
        case 3:
            setT(value);
            break;
        default:
            break;
    }
}

std::pair<std::string, double> LorenzAttractor::getParameter(int index) {
    switch (index) {
        case 0:
            return std::make_pair("Sigma", getSigma());
        case 1:
            return std::make_pair("Rho", getRho());
        case 2:
            return std::make_pair("Beta", getBeta());
        case 3:
            return std::make_pair("Time Factor", getT());
        default:
            break;
    }
}

void LorenzAttractor::resetParameters() {
    m_sigma = 10.0;
    m_rho = 28.0;
    m_beta = 8.0 / 3.0;
    m_t = 0.01;
}

// Setters
void LorenzAttractor::setSigma(double sigma){
    m_sigma = sigma;
}

void LorenzAttractor::setRho(double rho) {
    m_rho = rho;
}

void LorenzAttractor::setBeta(double beta) {
    m_beta = beta;
}

void LorenzAttractor::setT(double t) {
    m_t = t;
}

// Getters
double LorenzAttractor::getSigma() {
    return m_sigma;
}

double LorenzAttractor::getRho() {
    return m_rho;
}

double LorenzAttractor::getBeta() {
    return m_beta;
}

double LorenzAttractor::getT() {
    return m_t;
}
