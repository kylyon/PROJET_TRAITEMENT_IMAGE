#ifndef IMAGE_H
#define IMAGE_H
#include <vector>
#include "Pixel.h"
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "lib/stb/stb_image.h"
#include "lib/stb/stb_image_write.h"

#define RED 0
#define GREEN 1
#define BLUE 2

using std::vector;

class Image
{
    public:
        Image(char* filename);
        int getWidth() const;
        int getHeight() const;
        uint8_t* getPixels() const;
        //uint8_t* rgb_array();
        virtual ~Image();
        uint8_t& operator() (int x, int y, int color);

    protected:

    private:
        int width, height, bpp;
        uint8_t* pixels;
};

#endif // IMAGE_H
