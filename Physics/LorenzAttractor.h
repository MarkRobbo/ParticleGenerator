//
// Created by mark on 28/09/16.
//

#ifndef PARTICLEGENERATOR_LORENZATTRACTOR_H
#define PARTICLEGENERATOR_LORENZATTRACTOR_H


#include "Physics.h"

class LorenzAttractor : public Physics {
    private:
        double m_sigma;
        double m_rho;
        double m_beta;
        double m_t;
    public:
        LorenzAttractor(double sigma = 10.0, double rho = 28.0, double beta = 8.0 / 3.0, double t = 0.01);
        void applyPhysics(Particle* theParticle, double time);
        std::string getName();
        void setSigma(double sigma);
        void setRho(double rho);
        void setBeta(double beta);
        void setT(double t);
        double getSigma();
        double getRho();
        double getBeta();
        double getT();
        int getNumEditableParameters();
        void setParameter(int index, double value);
        std::pair<std::string, double> getParameter(int index);
        void resetParameters();
};


#endif //PARTICLEGENERATOR_LORENZATTRACTOR_H
