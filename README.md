# C++ Projects

## Particle Explosion

This program uses the Simple DirectMedia Layer [(SDL)](https://www.libsdl.org) to create a window where a swarm of particles performs an explosion-like motion with color-change.

<img width="822" alt="particle_explosion_blue" src="https://cloud.githubusercontent.com/assets/16541141/24647314/b6374506-191f-11e7-8d41-ad3d98f3677e.png">

The project is based on a free [udemy-course](https://www.udemy.com/free-learn-c-tutorial-beginners/). For the setup of SDL, see this [tutorial](http://lazyfoo.net/tutorials/SDL/01_hello_SDL/index.php). On my mac, I used Homebrew via `brew install sdl2` and compiled with g++ including the SDL-files with `g++ explosion.cpp -o explosion -I/usr/local/Cellar/sdl2/2.0.5/include/SDL2 -D_THREAD_SAFE -L/usr/local/lib -lSDL2`).
