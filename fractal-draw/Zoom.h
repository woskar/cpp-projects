#ifndef ZOOM_H_
#define ZOOM_H_

struct Zoom {
	int x{0};
	int y{0};
	double scale{0.0};

    // Constructor 
	Zoom(int x, int y, double scale) : x(x), y(y), scale(scale) {};
};

#endif
