#include <iostream>
#include <cstdint>
#include <memory>
#include "Bitmap.h"
#include "Mandelbrot.h"
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

    // Create Histogram for all the different iterations per pixels
    // array of integers stores the number of pixels, array index is number of iterations
    unique_ptr<int[]> histogram(new int[Mandelbrot::MAX_ITERATIONS + 1]{});

    // set whole screen to color
    for(int y = 0; y<HEIGHT; ++y)
    {
        for(int x=0; x<WIDTH; ++x)
        {
            //bitmap.setPixel(x, y, 255, 0, 0);

            // a temporary coordinate transformation
            double xFractal = (x - WIDTH/2 - 150)* 2.0/HEIGHT;
            double yFractal = (y - HEIGHT/2)* 2.0/HEIGHT;
            // get iterations for every Pixel
            int iterations = Mandelbrot::getIterations(xFractal, yFractal);
            // fill up histogram
            histogram[iterations]++;
            uint8_t color = (uint8_t)(256 * (double)iterations/Mandelbrot::MAX_ITERATIONS);
            color = color*color*color; // will not overflow as we use uint8_t
            bitmap.setPixel(x,y,0,color,0);

            if(yFractal < min) min = yFractal;
            if(yFractal > max) max = yFractal;
        }
    }

    cout << min << ", " << max << endl;

    bitmap.write("test.bmp");
    cout << "Program finished." << endl;
    return 0;
}
