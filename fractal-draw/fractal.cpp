#include <iostream>
#include <cstdint>
#include <memory>
#include <cmath>
#include "Bitmap.h" // define Bitmap Properties
#include "Mandelbrot.h"
#include "Zoom.h" // Zoom class
#include "ZoomList.h" // Store Zooms in vector
#include "FractalCreator.h"
using namespace std;

// We want to write a Fractal Image to a bitmap, so we need
// a Fractal class:
// a Bitmap class: Bitmap.h

int main()
{
    int const WIDTH = 800;
    int const HEIGHT = 600;
    // Create a bitmap Object and write
    Bitmap bitmap(WIDTH, HEIGHT);
    // set one pixel for test purpose
    // Bitmap has origin in lower left
    bitmap.setPixel(WIDTH/2, HEIGHT/2, 255, 255, 255); //RGB

    double min = 999999;
    double max = -999999;

    // Create a ZoomList to store the applied zooms
    ZoomList zoomList(WIDTH, HEIGHT);
    zoomList.add(Zoom(WIDTH/2, HEIGHT/2, 4.0/WIDTH));
    zoomList.add(Zoom(295, HEIGHT - 202, 0.1));
    zoomList.add(Zoom(313, HEIGHT - 300, 0.01));

    // Create Histogram for all the different iterations per pixels
    // array of integers stores the number of pixels, array index is number of iterations
    unique_ptr<int[]> histogram(new int[Mandelbrot::MAX_ITERATIONS ]{0});
    // Store number of iterations for every pixel
    unique_ptr<int[]> fractal(new int[WIDTH*HEIGHT]{0});

    // set whole screen to color
    for(int y = 0; y<HEIGHT; ++y)
    {
        for(int x=0; x<WIDTH; ++x)
        {
            pair<double, double> coords = zoomList.doZoom(x, y);
            // get iterations for every Pixel
            int iterations = Mandelbrot::getIterations(coords.first, coords.second);

            fractal[y*WIDTH+x] = iterations;

            // fill up histogram, but not last histogram-bin
            if(iterations != Mandelbrot::MAX_ITERATIONS){
                histogram[iterations]++;
            }

/*  Old Color-Calculation:
            uint8_t color = (uint8_t)(256 * (double)iterations/Mandelbrot::MAX_ITERATIONS);
            color = color*color*color; // will not overflow as we use uint8_t
            bitmap.setPixel(x,y,0,color,0);
            if(yFractal < min) min = yFractal;
            if(yFractal > max) max = yFractal;
*/
        }
    }

/*
    // Check if histogram works as intended
    cout << endl;
    int count = 0;
    for(int i=0; i<Mandelbrot::MAX_ITERATIONS; ++i)
    {
        cout << histogram[i] << " " << flush;
        count += histogram[i];
    }
    cout << count << "; " << WIDTH*HEIGHT << endl;
    cout << endl;

    cout << min << ", " << max << endl;
*/

    int total = 0;
    for(int i=0; i<Mandelbrot::MAX_ITERATIONS; ++i)
        total += histogram[i];

    for(int y = 0; y<HEIGHT; ++y)
    {
        for(int x=0; x<WIDTH; ++x)
        {
            uint8_t red = 0;
            uint8_t green = 0;
            uint8_t blue = 0;
            int iterations = fractal[y*WIDTH+x];

            // leave points with max iteration black
            if(iterations != Mandelbrot::MAX_ITERATIONS)
            {
                // change color proportional to number of pixels
                double hue = 0.0;
                for(int i=0; i<= iterations; ++i)
                    hue += ((double)histogram[i])/total;
                green = pow(255, hue); // hue ranges from 0 to 1
            }
            bitmap.setPixel(x,y,red,green,blue);
        }
    }

    bitmap.write("test.bmp");
    cout << "Program finished." << endl;
    return 0;
}
