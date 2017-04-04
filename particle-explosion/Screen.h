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
    Uint32 * m_buffer;

public:
    // Constructor with initializer list
    Screen()
    : m_window(NULL)
    , m_renderer(NULL)
    , m_texture(NULL)
    , m_buffer(NULL)
    {}

    // True if init succeeds
    bool init()
    {
        if(SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            cout << "SDL_init failed." << endl;
            return false;
        }

        m_window = SDL_CreateWindow("Particle Fire Explosion",
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

        m_buffer = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];

        // make window white by setting all bytes in buffer to maximum value (255 = 0xFF)
        // if value is 0, then screen is black.
        memset(m_buffer, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));


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

        // go to right pixel and set color
        m_buffer[(y * SCREEN_WIDTH) + x] = color;
    }

    // Clear the screen 
    void clear()
    {
        memset(m_buffer, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
    }

    // updating the screen
    void update()
    {
        // Drawing Code, putting pixel data to screen:
        SDL_UpdateTexture(m_texture, NULL, m_buffer, SCREEN_WIDTH * sizeof(Uint32));
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
        delete[] m_buffer;
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyTexture(m_texture);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
    }
};

#endif
