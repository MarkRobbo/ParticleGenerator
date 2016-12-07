//
// Created by mark on 28/09/16.
//

#include "ParticleManager.h"

// Static variables
int ParticleManager::m_numParticles;
Particle *ParticleManager::m_particleArray[MAX_PARTICLES];
Physics *ParticleManager::m_currentPhysics;
bool ParticleManager::m_lifetimeEnabled;

// Constructor to set up number of particles and assign given physics
ParticleManager::ParticleManager(Physics *thePhysics) {
    m_numParticles = 0;
    m_currentPhysics = thePhysics;
    m_lifetimeEnabled = true;
};

// New timestep occurred in the world, run physics on each particle
void ParticleManager::timeStep(double time) {
    for (int i = 0; i < m_numParticles; i++) {
        double newLife = m_particleArray[i]->getLife() - time;
        m_particleArray[i]->setLife(newLife);
        if (m_lifetimeEnabled && newLife <= 0) {
            deleteParticle(i);
        } else {
            m_currentPhysics->applyPhysics(m_particleArray[i], time);
        }
    }
}

// Add a new particle to the world
void ParticleManager::addParticle(Particle *newParticle) {
    m_particleArray[m_numParticles] = newParticle;
    m_numParticles++;
};

// Remove a particular particle from the world
void ParticleManager::deleteParticle(int index) {
    delete m_particleArray[index];

    // Move particle at end of array to deleted position and decrease num of particles
    m_particleArray[index] = m_particleArray[m_numParticles - 1];
    m_particleArray[m_numParticles] = NULL;
    m_numParticles--;
}

// Remove all particles from the world
void ParticleManager::clearParticles() {
    for (int i = 0; i < m_numParticles; i++) {
        delete m_particleArray[m_numParticles];
        m_particleArray[m_numParticles] = NULL;
    }
    m_numParticles = 0;
}

// Change the physics of the world
void ParticleManager::setPhysics(Physics *newPhysics) {
    delete m_currentPhysics;
    m_currentPhysics = newPhysics;
};

// Get a particle at a particular index
Particle *ParticleManager::getParticle(int index) {
    return m_particleArray[index];
};

// Get number of particles
int ParticleManager::getNumParticles() {
    return m_numParticles;
}

// Get the current physics object
Physics *ParticleManager::getPhysics() {
    return m_currentPhysics;
}

// Set whether lifetime is enabled
void ParticleManager::setLifetimeEnabled(bool m_lifetimeEnabled) {
    ParticleManager::m_lifetimeEnabled = m_lifetimeEnabled;
}
