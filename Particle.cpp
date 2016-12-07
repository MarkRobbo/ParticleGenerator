//
// Created by mark on 28/09/16.
//

#include "Particle.h"

// Constructor to set up position and colour
Particle::Particle(double x, double y, double z,
                   unsigned char r /* = 255 */, unsigned char g /* = 255 */, unsigned char b /* = 255 */,
                   double xVelocity /* = 0 */, double yVelocity /* = 0 */, double zVelocity /* = 0 */,
                   float size /* = 4 */, double life /* = 9999.9 */) {
    m_pos = std::make_tuple(x, y, z);
    m_color = std::make_tuple(r, g, b);
    m_velocity = std::make_tuple(xVelocity, yVelocity, zVelocity);
    m_size = size;
    m_life = life;
}

// Getters
std::tuple<double, double, double> Particle::getPos() {
    return m_pos;
}

std::tuple<unsigned char, unsigned char, unsigned char> Particle::getColor() {
    return m_color;
}

std::tuple<double, double, double> Particle::getVelocity() {
    return m_velocity;
}

std::tuple<double, double, double> Particle::getPrevVelocity() {
    return m_prev_velocity;
}

float Particle::getSize() {
    return m_size;
}

double Particle::getLife() {
    return m_life;
}

// Setters
void Particle::setPos(double x, double y, double z) {
    m_pos = std::make_tuple(x, y, z);
}

void Particle::setColor(unsigned char x, unsigned char y, unsigned char z) {
    m_color = std::make_tuple(x, y, z);
}

void Particle::setVelocity(double xVelocity, double yVelocity, double zVelocity) {
    m_velocity = std::make_tuple(xVelocity, yVelocity, zVelocity);
}

void Particle::setPrevVelocity(std::tuple<double, double, double> prevVelocity) {
    m_prev_velocity = prevVelocity;
}

void Particle::setSize(float size) {
    m_size = size;
}

void Particle::setLife(double life) {
    m_life = life;
}