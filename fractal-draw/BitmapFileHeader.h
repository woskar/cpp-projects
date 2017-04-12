#ifndef BITMAPFILEHEADER_H_
#define BITMAPFILEHEADER_H_

#include <cstdint> //for int32_t, a 32-bit-integer, because of fixed file format
using namespace std;

#pragma pack(2) //preprocessor directive to turn padding off

// Struct to have right beginning of Bitmap File
struct BitmapFileHeader {
	char header[2] { 'B', 'M' };
	int32_t fileSize;
	int32_t reserved {0};
	int32_t dataOffset; //how long into the file the actual Data begins
};

#endif /* BITMAPFILEHEADER_H_ */
