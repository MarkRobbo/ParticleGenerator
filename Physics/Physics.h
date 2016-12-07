//
// Created by mark on 28/09/16.
//

#ifndef PARTICLEGENERATOR_SIMULATION_H
#define PARTICLEGENERATOR_SIMULATION_H


#include "../Particle.h"

/* Abstract class representing the physics in the world

   A class extending this must implement the applyPhysics function which is called by ParticleManager
   and applies physics to a particle
    */

class Physics {
    public:
        virtual void applyPhysics(Particle* theParticle, double time) = 0;
        virtual std::string getName() = 0;
        virtual int getNumEditableParameters() = 0;
        virtual void setParameter(int index, double value) = 0;
        virtual std::pair<std::string, double> getParameter(int index) = 0;
        virtual void resetParameters() = 0;
};


#endif //PARTICLEGENERATOR_SIMULATION_H
