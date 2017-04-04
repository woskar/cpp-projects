// run with:
// g++ SDLbasics.cpp -o sdl -I/usr/local/Cellar/sdl2/2.0.5/include/SDL2 -D_THREAD_SAFE -L/usr/local/lib -lSDL2

#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <SDL.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "Screen.h"
#include "Swarm.h"
using namespace std;

int main()
{
    // Random number generator
    srand(time(NULL));

    // create a Screen object
    Screen screen;

    if(screen.init() == false)
        cout << "Error initializing SDL." << endl;

    // create a Swarm
    Swarm swarm;

    while(true)
    {
        // Update particles

        // return the number of seconds since program started
        int elapsed = SDL_GetTicks();

        // Draw particles
        const Particle * const pParticles = swarm.getParticles();

        // Update positions of all of the particles
        swarm.update(elapsed);

        // Clear screen to have blank canvas
        screen.clear();


        // create changing colors based on elapsed time
        int red = (1 + cos(elapsed*0.001)) * 128;
        int green = (1 + sin((elapsed+0.003)*0.0025)) * 128;
        int blue = (1 + sin(elapsed*0.003)) * 128;

        for(int i=0; i<Swarm::NPARTICLES; ++i)
        {
            Particle particle = pParticles[i];
            int x = (particle.m_x + 1) * Screen::SCREEN_WIDTH/2;
            int y = particle.m_y * Screen::SCREEN_WIDTH/2 + Screen::SCREEN_HEIGHT/2;

            screen.setPixel(x, y, red, green, blue);
        }

        // Draw the screen
        screen.update();

        // Check for messages/events
        if(screen.processEvents() == false)
            break;
    }

    screen.close();
    return 0;


}
