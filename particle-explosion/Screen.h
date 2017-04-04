// Screen.h

#ifndef SCREEN_H
#define SCREEN_H

#include <iostream>
#include <iomanip>
using namespace std;

class Screen
{
public:
    const static int SCREEN_WIDTH = 800;
    const static int SCREEN_HEIGHT = 600;

private:
    SDL_Window * m_window;
    SDL_Renderer * m_renderer;
    SDL_Texture * m_texture;
    Uint32 * m_buffer1;
    Uint32 * m_buffer2; //second buffer for blur screen

public:
    // Constructor with initializer list
    Screen()
    : m_window(NULL)
    , m_renderer(NULL)
    , m_texture(NULL)
    , m_buffer1(NULL)
    , m_buffer2(NULL)
    {}

    // True if init succeeds
    bool init()
    {
        if(SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            cout << "SDL_init failed." << endl;
            return false;
        }

        m_window = SDL_CreateWindow("Particle Explosion",
                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if(m_window == NULL)
        {
            SDL_Quit();
            printf("Could not create window: %s\n", SDL_GetError());
            return false;
        }

        m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
        m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);

        if(m_renderer == NULL)
        {
            cout << "Could not create renderer" << endl;
            SDL_DestroyWindow(m_window);
            SDL_Quit();
            return false;
        }

        if(m_texture == NULL)
        {
            cout << "Could not create texture" << endl;
            SDL_DestroyRenderer(m_renderer);
            SDL_DestroyWindow(m_window);
            SDL_Quit();
            return false;
        }

        // if everything worked out, allocate buffers
        m_buffer1 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
        m_buffer2 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];

        // clear buffer, else there could be garbage
        memset(m_buffer1, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
        memset(m_buffer2, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));

        // set individual pixel to white
        //m_buffer[2403] = 0xFFFFFFFF; // two f's for each red, green, blue, alpha
    /*
        // set whole screen to certain color by looping over pixels:
        for(int i=0; i<SCREEN_WIDTH*SCREEN_HEIGHT; ++i)
            m_buffer[i] = 0xFFFF00FF;
    */
        return true;
    }


    // set Pixel at xy-Coordinate with color
    void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue)
    {
        if(x<0 || x >= SCREEN_WIDTH ||  y<0 || y >= SCREEN_HEIGHT)
            return;

        Uint32 color = 0;
        // compose Hex-Color 0xrrggbbaa by adding and bitshift
        color += red;
        color <<= 8;
        color += green;
        color <<= 8;
        color += blue;
        color <<= 8;
        color += 0xFF; //for alpha value

        // go to right pixel and set color in buffer1
        m_buffer1[(y * SCREEN_WIDTH) + x] = color;
    }

    // Create a new screen with traces of particles
    void boxBlur()
    {
        // write to buffer1, which is the one drawing to the screen
        // swap pointers and store buffer1 into buffer2
        Uint32 * temp = m_buffer1; // temporary buffer for swap
        m_buffer1 = m_buffer2;
        m_buffer2 = temp;

        // Iterate over all pixels, apply blur algorithm, store to buffer1
        for(int y=0; y<SCREEN_HEIGHT; ++y)
        {
            for(int x=0; x<SCREEN_WIDTH; ++x)
            {
                /*
                 * Box blur will be created by averaging over 9 pixels
                 * 0 0 0
                 * 0 1 0
                 * 0 0 0
                 */

                int redTotal = 0;
                int greenTotal = 0;
                int blueTotal = 0;

                for(int row=-1; row<=1; row++)
                {
                    for(int col=-1; col<=1; col++)
                    {
                        int currentX = x + col;
                        int currentY = y + row;

                        // make sure we stay inside the borders of our window
                        if(currentX >= 0 && currentX < SCREEN_WIDTH && currentY >= 0 && currentY < SCREEN_HEIGHT)
                        {
                            Uint32 color = m_buffer2[currentY*SCREEN_WIDTH + currentX];

                            Uint8 red = color >> 24;
                            Uint8 green = color >> 16;
                            Uint8 blue = color >> 8;

                            redTotal += red;
                            greenTotal += green;
                            blueTotal += blue;
                        }
                    }
                }
                Uint8 red = redTotal/9;
                Uint8 green = greenTotal/9;
                Uint8 blue = blueTotal/9;

                setPixel(x, y, red, green, blue);
            }
        }
    }

    // Clear the screen
    void clear()
    {
        memset(m_buffer1, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
        memset(m_buffer2, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
    }

    // updating the screen
    void update()
    {
        // Drawing Code, putting pixel data to screen:
        SDL_UpdateTexture(m_texture, NULL, m_buffer1, SCREEN_WIDTH * sizeof(Uint32));
        SDL_RenderClear(m_renderer);
        SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
        SDL_RenderPresent(m_renderer);
    }

    // Eventprocessing
    bool processEvents()
    {
        SDL_Event event;
        // checks all the events, if any are Quit, so quit.
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                return false;
            }
        }
        return true;
    }

    // Deallocation/Close-down function
    void close()
    {
        delete[] m_buffer1;
        delete[] m_buffer2;
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyTexture(m_texture);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
    }
};

#endif
