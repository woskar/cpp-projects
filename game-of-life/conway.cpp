#include "image.hpp"
#include <iostream>
#include <cassert>

int count_alive_neighbors(Image const & image, int x, int y);
Image conway_step(Image const & image);
Image scale_image(Image const & image, int scale);


int main()
{

    // Simulation:
    Image init = readPGM("my_conway.pgm");
    std::string number;
    std::string version;

    int i = 0;
    while(i < 100)
    {
        init = conway_step(init);
        if(i < 10)
            number = "00" + std::to_string(i);
        else if (i >= 10 && i <100)
            number = "0" + std::to_string(i);
        version = "conway_sim_" + number + ".pgm";
        writePGM(scale_image(init, 7), version);
        ++i;
    }

/*
    Generate a Simulation with the resulting pictures using
    "convert -delay 6 conway_sim_*.pgm simulation.mpg"
    on the command line with ImageMagick installed.
*/

/*
    Image init = readPGM("conway_init.pgm");
    for(int i = 0; i < 100; ++i)
    {
        init = conway_step(init);
    }
    init = scale_image(init, 5);
    writePGM(init, "conway_result.pgm");
    Image test = readPGM("conway_test.pgm");
    assert(init == test);
    std::cout << "Yeah, it worked!" << std::endl;
*/
    return 0;
}


int count_alive_neighbors(Image const & image, int x, int y)
{
    int count = 0;
    if(image.get_periodic(x-1, y-1) == 0) ++count;
    if(image.get_periodic(x  , y-1) == 0) ++count;
    if(image.get_periodic(x+1, y-1) == 0) ++count;
    if(image.get_periodic(x+1, y  ) == 0) ++count;
    if(image.get_periodic(x+1, y+1) == 0) ++count;
    if(image.get_periodic(x  , y+1) == 0) ++count;
    if(image.get_periodic(x-1, y+1) == 0) ++count;
    if(image.get_periodic(x-1, y  ) == 0) ++count;
    //if(count > 1)
    //std::cout << "Count is " << count << " at " << x << ", "<< y << std::endl;
    return count;
}

Image conway_step(Image const & image)
{
    Image new_image(image.width(), image.height());
    for(int y=0, h=image.height(); y<h; ++y)
    {
        for(int x=0, w=image.width(); x<w; ++x)
        {
            int neighbors = count_alive_neighbors(image, x, y);
            if(neighbors < 2)
                new_image(x,y) = 255;
            else if(neighbors == 2 && image(x,y) == 0)
                new_image(x,y) = 0;
            else if(neighbors == 3)
                new_image(x,y) = 0;
            else if(neighbors > 4 && image(x,y) == 0)
                new_image(x,y) = 255;
            else
                new_image(x,y) = 255;
        }
    }
    return new_image;
}

Image scale_image(Image const & image, int scale)
{
    Image result(scale*image.width(), scale*image.height());
    for(int y=0, h=result.height(); y<h; ++y)
    {
        for(int x=0, w=result.width(); x<w; ++x)
        {
            result(x,y) = image(x/scale, y/scale);
        }
    }
    return result;
}
