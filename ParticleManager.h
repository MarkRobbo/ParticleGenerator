//
// Created by mark on 28/09/16.
//

#ifndef PARTICLEGENERATOR_PARTICLEMANAGER_H
#define PARTICLEGENERATOR_PARTICLEMANAGER_H


#include "Particle.h"
#include "Physics/Physics.h"

const int MAX_PARTICLES = 150000;

class ParticleManager {
    private:
        static int m_numParticles;
        static Particle *m_particleArray[MAX_PARTICLES];
        static Physics *m_currentPhysics;
        static bool m_lifetimeEnabled;
    public:
        ParticleManager(Physics *thePhysics);
        void timeStep(double time);
        void addParticle(Particle *newParticle);
        void deleteParticle(int index);
        void clearParticles();
        Physics *getPhysics();
        void setPhysics(Physics *newPhysics);
        int getNumParticles();
        Particle *getParticle (int index);

    static void setLifetimeEnabled(bool m_lifetimeEnabled);
};


#endif //PARTICLEGENERATOR_PARTICLEMANAGER_H
