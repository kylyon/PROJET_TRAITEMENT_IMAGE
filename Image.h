#ifndef IMAGE_H
#define IMAGE_H
#include <vector>
#include <string>
#include "Pixel.h"
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "lib/stb/stb_image.h"
#include "lib/stb/stb_image_write.h"

#define RED 0
#define GREEN 1
#define BLUE 2
#define ALPHA 3

using std::vector;
using std::string;

class Image
{
    public:
        Image(char* filename);
        Image(int height, int width);
        int getWidth() const;
        int getHeight() const;
        uint8_t* getPixels() const;
        //uint8_t* rgb_array();
        virtual ~Image();
        uint8_t& operator() (int x, int y, int color);
        void const save(char* filename) const;
        void crop(int top,int bottom,int left,int right);
        Image mask(Image background);
        int getCenter(string cen);


    protected:

    private:
        int width, height, bpp;
        uint8_t* pixels;
};

#endif // IMAGE_H
