#ifndef FRACTALCREATOR_H_
#define FRACTALCREATOR_H_

#include <string>
#include <string>
#include <cstdint>
#include <memory>
#include <cmath>
#include "Zoom.h"
#include "Mandelbrot.h"
#include "Bitmap.h"
#include "ZoomList.h"
#include "RGB.h"

using namespace std;

class FractalCreator {
private:
    int m_width;
	int m_height;
	unique_ptr<int[]> m_histogram;
	unique_ptr<int[]> m_fractal;
	Bitmap m_bitmap;
	ZoomList m_zoomList;
	int m_total { 0 };

private:
    void calculateIteration();
	void calculateTotalIterations();
	void drawFractal();
	void addZoom(const Zoom& zoom);
	void writeBitmap(string name);

public:
	FractalCreator(int width, int height);
	virtual ~FractalCreator(){}
    // run now does all of the magic by calling the other functions
	void run(string name);
};

// Implementations of obove Methods:

void FractalCreator::run(string name) {
	addZoom(Zoom(295, m_height - 202, 0.1));
	addZoom(Zoom(313, m_height - 300, 0.01));
	calculateIteration();
	calculateTotalIterations();
	drawFractal();
	writeBitmap("test.bmp");

}

FractalCreator::FractalCreator(int width, int height)
: m_width(width)
, m_height(height)
, m_histogram(new int[Mandelbrot::MAX_ITERATIONS] { 0 })
, m_fractal(new int[m_width * m_height] { 0 })
, m_bitmap(m_width, m_height)
, m_zoomList(m_width, m_height)
{
	m_zoomList.add(Zoom(m_width / 2, m_height / 2, 4.0 / m_width));
}

void FractalCreator::calculateIteration() {

	for (int y = 0; y < m_height; y++)
    {
		for (int x = 0; x < m_width; x++)
        {
			pair<double, double> coords = m_zoomList.doZoom(x, y);
			int iterations = Mandelbrot::getIterations(coords.first, coords.second);
			m_fractal[y * m_width + x] = iterations;

			if (iterations != Mandelbrot::MAX_ITERATIONS)
            {
				m_histogram[iterations]++;
			}
		}
	}
}

void FractalCreator::calculateTotalIterations()
{
	for (int i = 0; i < Mandelbrot::MAX_ITERATIONS; i++)
    {
		m_total += m_histogram[i];
	}
}

void FractalCreator::drawFractal()
{
    RGB startColor(0,0,0);
    RGB endColor(0,255,0);
    RGB colorDiff = endColor - startColor;

	for (int y = 0; y < m_height; y++)
    {
		for (int x = 0; x < m_width; x++)
        {
			uint8_t red = 0;
			uint8_t green = 0;
			uint8_t blue = 0;
			int iterations = m_fractal[y * m_width + x];
			if (iterations != Mandelbrot::MAX_ITERATIONS)
            {
				double hue = 0.0;
				for (int i = 0; i <= iterations; i++)
					hue += ((double) m_histogram[i]) / m_total;
                red = startColor.r + colorDiff.r * hue;
                green = startColor.g + colorDiff.g * hue;
                blue = startColor.b + colorDiff.b * hue;
			}
			m_bitmap.setPixel(x, y, red, green, blue);
		}
	}
}

void FractalCreator::addZoom(const Zoom& zoom)
{
	m_zoomList.add(zoom);
}

void FractalCreator::writeBitmap(string name)
{
	m_bitmap.write(name);
}

#endif
