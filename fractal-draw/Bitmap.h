#ifndef BITMAP_H_
#define BITMAP_H_

#include <string>
#include <cstdint> // for uint_t which is an unsigned char
#include <fstream> // to write a binary file

#include "BitmapFileHeader.h"
#include "BitmapInfoHeader.h"

using namespace std;

// we need a pointer to an area of memory big enough to hold
// all the information of all the pixels in the screen

class Bitmap {
private:
	int m_width{0};
	int m_height{0};
    unique_ptr<uint8_t[]> m_pPixel{nullptr};
    // we do not have to put delete in the destructor
    // this would be necessary with a normal pointer

public:
    // Constructor to inizialize the Bitmap
	Bitmap(int width, int height)
    :m_width(width), m_height(height), m_pPixel(new uint8_t[width*height*3]{}){}

    // Allows to set pixels and specify colors
	void setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue)
    {
        // Create Pointer pixel-data and move it by pointer arithmetic
        uint8_t *pPixel = m_pPixel.get();
        pPixel += (y*3) * m_width + (x*3); //*3 because of RGB
        pPixel[0] = blue; // reverse order because BMP is little endian format
        pPixel[1] = green;
        pPixel[2] = red;

    }

    // Write to the created Bitmap Object
    // will return false if it does not succeed
    bool write(string filename)
    {
        BitmapFileHeader fileHeader;
        BitmapInfoHeader infoHeader;
        // *3 because every Pixel will take up 3 byte (RGB)
        fileHeader.fileSize = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader) + m_width*m_height*3;
        // Distance from the File to where the Data actually starts
        fileHeader.dataOffset = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader);
        // Info header contains the information about the bitmap
        infoHeader.width = m_width;
        infoHeader.height = m_height;
        // write to binary file with ofstream
        ofstream file;
        file.open(filename, ios::out|ios::binary);
        // check for error condition
        if(!file) return false;
        // write data to the file, char* is old-style-cast,
        // write expects char* pointer to file as first argument
        file.write((char*)&fileHeader, sizeof(fileHeader)); // adress, number of bytes to write
        file.write((char*)&infoHeader, sizeof(infoHeader));
        file.write((char*)m_pPixel.get(), m_width*m_height*3); // .get() gives a normal pointer of the unique_ptr
        // close the file
        file.close();
        //check again to make sure closing went well
        if(!file) return false;
        // we return true if all went
        return true;
    }


	virtual ~Bitmap(){};
    // we used a unique_ptr, it will clean up the memory
};


#endif
