//
// Created by mark on 29/09/16.
//

#ifndef PARTICLEGENERATOR_EMITTER_H
#define PARTICLEGENERATOR_EMITTER_H

#include <tuple>
#include "../ParticleManager.h"

/* Class representing a particle emitter in the world
   */

class Emitter {
    protected:
        std::tuple<double, double, double> m_pos;
        std::tuple<unsigned char, unsigned char, unsigned char> m_color;
        ParticleManager *m_particleManager;
        float getRand();
    public:
        Emitter(ParticleManager *particleManager, double x = 0.0, double y = 0.0, double z = 0.0,
                unsigned char r = 0, unsigned char g = 100, unsigned char b = 0);
        virtual void emitParticles(int numParticles) = 0;
        virtual std::string getName() = 0;
        ParticleManager *getParticleManager();
        std::tuple<double, double, double> getPos();
        std::tuple<unsigned char, unsigned char, unsigned char> getColor();
        void setPos(double x, double y, double z);
        void setColor(unsigned char r, unsigned char g, unsigned char b);
        void setParticleManager(ParticleManager *particleManager);
};


#endif //PARTICLEGENERATOR_EMITTER_H
