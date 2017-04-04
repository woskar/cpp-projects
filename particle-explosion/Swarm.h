#ifndef SWARM_H
#define SWARM_H

#include "Particle.h"

class Swarm {
// A Swarm is an array of particles
public:
    const static int NPARTICLES = 3000;

private:
    Particle * m_pParticles;
    int lastTime; //will store when Swarm position was last updated

public:
    Swarm()
    : lastTime(0) //Initialize last updating Time to zero
    {
        m_pParticles = new Particle[NPARTICLES];
    }

    ~Swarm()
    {
        delete[] m_pParticles;
    }

    const Particle * const getParticles()
    {
        return m_pParticles;
    }

    // update should change the position based on the elapsed time
    // this makes sure the animation is going in the same speed on every system
    void update(int elapsed)
    {
        int interval = elapsed - lastTime; // calculate passed time since last update
        for(int i=0; i<Swarm::NPARTICLES; ++i)
        {
            m_pParticles[i].update(interval);
        }
        lastTime = elapsed; //store present time
    }

};

#endif
