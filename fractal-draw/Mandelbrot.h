#ifndef MANDELBROT_H_
#define MANDELBROT_H_

#include <complex>
using namespace std;

class Mandelbrot {
public:
    // the more iterations the better the quality of the image
	static const int MAX_ITERATIONS = 1000;

public:
	Mandelbrot();
	virtual ~Mandelbrot();
    // make it static as we don't need any instance variables thereof
    // the iterations we get here will be mapped to the colors
	static int getIterations(double x, double y)
    {
        complex<double> z = 0;
        complex<double> c(x, y);

        int iterations = 0;

        while(iterations < MAX_ITERATIONS)
        {
            z = z*z + c;
            if(abs(z) > 2) break;
            iterations++;
        }
        return iterations;
    }
};

#endif /* MANDELBROT_H_ */
