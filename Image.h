#ifndef IMAGE_H
#define IMAGE_H
#include <vector>
#include "Pixel.h"
#define STB_IMAGE_IMPLEMENTATION
#include "lib/stb/stb_image.h"

using std::vector;

class Image
{
    public:
        Image(char* filename);
        int getWidth() const;
        int getHeight() const;
        vector<Pixel> getPixels() const;
        uint8_t* rgb_array();
        virtual ~Image();

    protected:

    private:
        int width, height, bpp;
        vector<Pixel> pixels;
};

#endif // IMAGE_H
