# C++ Projects

## Fractal Draw

The Fractal Drawer draws the Mandelbrot-Set on BMP Images. 

Code structure:
- main.cpp: main program connecting the classes
- fractal.cpp: old version before split up into classes
- FractalCreator.h: does the actual drawing
- RGB.h: Color handling
- Zoom.h: defining a zoom
- ZoomList.h: stores multiple Zooms in a vector
- Mandelbrot.h: contains the Math behind the fractal
- Bitmap.h: Initialize the BMP file
- BitmapFileHeader: first data in Bitmap
- BitmapInfoHeader: second data in Bitmap

Created April 2017

---

## Particle Explosion

This program uses the Simple DirectMedia Layer [(SDL)](https://www.libsdl.org) to create a window where a swarm of particles performs an explosion-like motion with color-change.

<img width="822" alt="particle_explosion_blue" src="https://cloud.githubusercontent.com/assets/16541141/24647314/b6374506-191f-11e7-8d41-ad3d98f3677e.png">

Detailed instructions on how to create such a simulation can be found in this free  [udemy-course](https://www.udemy.com/free-learn-c-tutorial-beginners/). For the setup of SDL, see this [tutorial](http://lazyfoo.net/tutorials/SDL/01_hello_SDL/index.php). On my mac, I used Homebrew via `brew install sdl2` and compiled with g++ including the SDL-files with `g++ explosion.cpp -o explosion -I/usr/local/Cellar/sdl2/2.0.5/include/SDL2 -D_THREAD_SAFE -L/usr/local/lib -lSDL2`).

Code structure:
- explosion.cpp: main program connects swarm and screen
- Screen.h: sdl setup, window management, event handling, blur algorithm
- Particle.h: particle class initializing and updating position and speed
- Swarm.h: creates and handles swarm as array of particles

Created April 2017

----

## Game of Life

This project was part of the C++ lecture ipi and is a simple implementation of Conway's [Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) using the image format [PGM](https://en.wikipedia.org/wiki/Netpbm_format) (Portable Graymap). 

![game-of-life](https://cloud.githubusercontent.com/assets/16541141/24961043/dd2b0ba6-1f97-11e7-91c7-f262ccbf2d31.png)

Given an initial configuration of pixels, which correspond to "living cells", the algorithm determines which pixels will be lit in the next iteration. The program outputs a series of pgm-images which can be converted into an animated film using ffmpeg or ImageMagick with the command `convert -delay 6 conway_sim_*.pgm simulation.mpg`.

The rules are: 
- cell with fewer than two live neighbours dies of isolation
- cell with two or three live neighbours lives on
- cell with more than three neighbours dies of overpopulation
- a dead cell with exactly three live neighbours becomes a live cell

Created March 2017
