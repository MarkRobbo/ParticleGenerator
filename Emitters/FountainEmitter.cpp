//
// Created by mark on 29/09/16.
//

#include "FountainEmitter.h"

// Run superclass constructor
FountainEmitter::FountainEmitter(ParticleManager *particleManager, double x, double y, double z,
                                 unsigned char r /* = 0 */, unsigned char g /* = 100 */, unsigned char b /* = 0 */)
        : Emitter(particleManager, x, y, z, r, g, b) {
}

// Emit a number of particles into the world using the particle manager
void FountainEmitter::emitParticles(int numParticles) {
    for (int i=0; i < numParticles; i++) {
        Particle *newParticle = new Particle(std::get<0>(m_pos) + getRand() - 0.5, std::get<1>(m_pos) + getRand() - 0.5, std::get<2>(m_pos) + getRand() - 0.5, // small variation in position
                                             std::get<0>(m_color), std::get<1>(m_color), std::get<2>(m_color),
                                             getRand() - 0.5, 1, getRand() - 0.5, 50.0, 1000.0);

        m_particleManager->addParticle(newParticle);
    }
}

std::string FountainEmitter::getName() {
    return "Fountain";
}