#include "Image.h"
#include "Pixel.h"
#include <vector>
#define STB_IMAGE_IMPLEMENTATION
#include "lib/stb/stb_image.h"

using std::vector;

Image::Image(char* filename)
{
    uint8_t* rgb_image = stbi_load("ciel.jpg", &this->width, &this->height, &this->bpp, 3);

    for(int i=0; i < width * height * 3; i++)
    {
        if(i%3 == 2)
        {
            Pixel p = Pixel(rgb_image[i-2], rgb_image[i-1], rgb_image[i]);
            this->pixels.push_back(p);
        }
    }
}

int Image::getWidth() const
{
    return this->width;
}

int Image::getHeight() const
{
    return this->height;
}

vector<Pixel> Image::getPixels() const
{
    return this->pixels;
}

uint8_t* Image::rgb_array()
{
    uint8_t* rgb_image;
    rgb_image = malloc(this->width*this->height*3);


    for(int i=0; i < this->width * this->height*3; i++)
    {
        switch(i%3)
        {
            case 0:
                rgb_image[i] = this->pixels[int(i/3)].getRed();
                break;
            case 1:
                rgb_image[i] = this->pixels[int(i/3)].getGreen();
                break;
            case 2:
                rgb_image[i] = this->pixels[int(i/3)].getBlue();
                break;
        }

    }

    return rgb_image;
}

Image::~Image()
{
    //dtor
}
