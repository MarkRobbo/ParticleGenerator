//
// Created by mark on 28/09/16.
//

#ifndef PARTICLEGENERATOR_PARTICLE_H
#define PARTICLEGENERATOR_PARTICLE_H


#include <tuple>

class Particle {
    private:
        std::tuple<double, double, double> m_pos;
        std::tuple<unsigned char, unsigned char, unsigned char> m_color;
        std::tuple<double, double, double> m_velocity;
        std::tuple<double, double, double> m_prev_velocity;
        float m_size;
        double m_life;
    public:
        Particle(double x, double y, double z,
                 unsigned char r = 255, unsigned char g = 255, unsigned char b = 255,
                 double xVelocity = 0, double yVelocity = 0, double zVelocity = 0,
                 float size = 4, double life = 9999.0);
        std::tuple<double, double, double> getPos();
        std::tuple<unsigned char, unsigned char, unsigned char> getColor();
        std::tuple<double, double, double> getVelocity();
        std::tuple<double, double, double> getPrevVelocity();
        float getSize();
        double getLife();
        void setPos(double x, double y, double z);
        void setColor(unsigned char x, unsigned char y, unsigned char z);
        void setVelocity(double xVelocity, double yVelocity, double zVelocity);
        void setPrevVelocity(std::tuple<double, double, double> prevVelocity);
        void setSize(float size);
        void setLife(double life);
};


#endif //PARTICLEGENERATOR_PARTICLE_H
