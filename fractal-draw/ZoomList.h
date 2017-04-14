#ifndef ZOOMLIST_H_
#define ZOOMLIST_H_

#include <vector> // for std::vector (obviously)
#include <utility> // for std::pair
#include <iostream> // for std::cout
#include "Zoom.h"

// Zoom List will store different Zooms

class ZoomList {
private:
    // every zoom will add to the x and y center values
	double m_xCenter{0};
	double m_yCenter{0};
	double m_scale{1.0};

    // we need to store width and height
	int m_width{0};
	int m_height{0};
	std::vector<Zoom> zooms;

public:
	ZoomList(int width, int height): m_width(width), m_height(height){}

    // Store a zoom in the Zoom-List
    void add(const Zoom& zoom)
    {
        // store zoom in the vector
        zooms.push_back(zoom);

        // work out where new center of screen will be after click
        m_xCenter += (zoom.x - m_width/2)*m_scale;
        m_yCenter += -(zoom.y - m_height/2)*m_scale;
        m_scale *= zoom.scale;
        //std::cout << m_xCenter << ", " << m_yCenter << ", " << m_scale << std::endl;
    }

    // map from bitmap-coordinates to fractal coordinates
	std::pair<double, double> doZoom(int x, int y)
    {
        double xFractal = (x - m_width / 2) * m_scale + m_xCenter;
    	double yFractal = (y - m_height / 2) * m_scale + m_yCenter;
    	return pair<double, double>(xFractal, yFractal);
    }
};

#endif
