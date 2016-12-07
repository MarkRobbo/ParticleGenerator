//
// Created by mark on 28/09/16.
//

#ifndef PARTICLEGENERATOR_NEWTONIAN_H
#define PARTICLEGENERATOR_NEWTONIAN_H


#include "Physics.h"

class Newtonian : public Physics {
    private:
        double m_gravity;
    public:
        Newtonian(double gravity = -9.81);
        void applyPhysics(Particle* theParticle, double time);
        std::string getName();
        void setGravity(double gravity);
        double getGravity();
        int getNumEditableParameters();
        void setParameter(int index, double value);
        std::pair<std::string, double> getParameter(int index);
        void resetParameters();
};


#endif //PARTICLEGENERATOR_NEWTONIAN_H
