//
// Created by mark on 29/09/16.
//

#include "Emitter.h"

Emitter::Emitter(ParticleManager *particleManager, double x /* = 0.0 */, double y /* = 0.0 */, double z /* = 0.0 */,
                 unsigned char r /* = 0 */, unsigned char g /* = 100 */, unsigned char b /* = 0 */) {
    m_particleManager = particleManager;
    m_pos = std::make_tuple(x, y, z);
    m_color = std::make_tuple(r, g, b);
}

// Helper function to generate a random number between 0 and 1
float Emitter::getRand() {
    return (float)(double) rand() / (RAND_MAX);
}

// Getters
std::tuple<double, double, double> Emitter::getPos() {
    return m_pos;
}

std::tuple<unsigned char, unsigned char, unsigned char> Emitter::getColor() {
    return m_color;
}

ParticleManager *Emitter::getParticleManager() {
    return m_particleManager;
}

// Setters
void Emitter::setPos(double x, double y, double z) {
    m_pos = std::make_tuple(x, y, z);
}

void Emitter::setColor(unsigned char r, unsigned char g, unsigned char b) {
    m_color = std::make_tuple(r, g, b);
}

void Emitter::setParticleManager(ParticleManager *particleManager) {
    m_particleManager = particleManager;
}
