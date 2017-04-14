#include <iostream>
#include "FractalCreator.h"
#include "RGB.h"
#include "Zoom.h"

using namespace std;

int main()
{
	FractalCreator fractalCreator(800, 600);
    // all pixels with same iterations will get same color
    // 0.3 stands for up to 300 iterations on the pixel
    fractalCreator.addRange(0.0, RGB(0, 0, 0));
    fractalCreator.addRange(0.1, RGB(255, 244, 0));
    fractalCreator.addRange(0.2, RGB(188, 255, 0));
    fractalCreator.addRange(0.3, RGB(0, 255, 74));
    fractalCreator.addRange(0.4, RGB(0, 255, 222));
    fractalCreator.addRange(0.5, RGB(0, 168, 255));
    fractalCreator.addRange(1.0, RGB(255, 255, 255));
    fractalCreator.addZoom(Zoom(295, 202, 0.1));
	fractalCreator.addZoom(Zoom(300, 350, 0.01));
	fractalCreator.run("test.bmp");
	cout << "Finished." << endl;
	return 0;
}
