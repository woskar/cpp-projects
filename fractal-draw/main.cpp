#include <iostream>
#include "FractalCreator.h"
#include "RGB.h"

using namespace std;

int main()
{
	FractalCreator fractalCreator(800, 600);
	fractalCreator.run("test.bmp");
	cout << "Finished." << endl;
	return 0;
}
