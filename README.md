# C++ Projects
- - -
## Paricle Explosion

This program uses the Simple DirectMedia Layer [(SDL)](https://www.libsdl.org) to create a window where a swarm of particles performs an explosion-like motion with color-change.

The project is based on a free [udemy-course](https://www.udemy.com/free-learn-c-tutorial-beginners/). For the setup of SDL, see this [tutorial](http://lazyfoo.net/tutorials/SDL/01_hello_SDL/index.php). On my mac, I used Homebrew (brew install sdl2) and compiled with g++ (including the SDL-files: g++ explosion.cpp -o explosion -I/usr/local/Cellar/sdl2/2.0.5/include/SDL2 -D_THREAD_SAFE -L/usr/local/lib -lSDL2).
