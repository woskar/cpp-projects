#ifndef PARTICLE_H
#define PARTICLE_H

#include <stdlib.h>
#include <math.h>

struct Particle {
    // Position of Particles
    double m_x;
    double m_y;

    // speed in cartesian coordinates
    //double m_xspeed;
    //double m_yspeed;

    // speed in polar coordinates
    double m_speed;
    double m_direction;

    // Constructor for Particles
    Particle()
    : m_x(0) //put all particles in center
    , m_y(0)
    {
        m_direction = (2 * M_PI * rand())/RAND_MAX;
        m_speed = (0.0001 * rand())/RAND_MAX;
        // older version: randomly distributed particles
        //m_x = ((2.0 * rand()) / RAND_MAX)-1;
        //m_y = ((2.0 * rand()) / RAND_MAX)-1;
        // older version: cartesian velocities
        //m_xspeed = 0.001 * (((2.0 * rand())/RAND_MAX)-1);
        //m_yspeed = 0.001 * (((2.0 * rand())/RAND_MAX)-1);
    }

    //Destructor
    ~Particle(){}

    // Change Positions of Particles
    void update(int interval)
    {
        double xspeed = m_speed * cos(m_direction);
        double yspeed = m_speed * sin(m_direction);

        m_x += xspeed * interval;
        m_y += yspeed * interval;

    /*    m_x += m_xspeed;
        m_y += m_yspeed;
        if(m_x < -1.0 || m_x >= 1.0) {
            m_xspeed = -m_xspeed;
            m_yspeed = -m_yspeed;
        }*/
    }

};

#endif
