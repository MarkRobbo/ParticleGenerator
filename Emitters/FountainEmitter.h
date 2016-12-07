//
// Created by mark on 29/09/16.
//

#ifndef PARTICLEGENERATOR_FOUNTAINEMITTER_H
#define PARTICLEGENERATOR_FOUNTAINEMITTER_H


#include "Emitter.h"

class FountainEmitter : public Emitter {
    public:
        FountainEmitter(ParticleManager *particleManager, double x, double y, double z,
                        unsigned char r = 0, unsigned char g = 100, unsigned char b = 0);
        void emitParticles(int numParticles);
        std::string getName();
};


#endif //PARTICLEGENERATOR_FOUNTAINEMITTER_H
