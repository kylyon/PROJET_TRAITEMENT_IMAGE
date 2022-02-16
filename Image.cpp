#include "Image.h"
#include "Pixel.h"
#include <vector>

using std::vector;
using namespace std;

Image::Image(char* filename)
{
    this->pixels = stbi_load(filename, &this->width, &this->height, &this->bpp, 4);
    this->offsetX = 0;
    this->offsetY = 0;
}

Image::Image(int height, int width)
{
    this->pixels = (uint8_t*) malloc(width*height*4);
    this->offsetX = 0;
    this->offsetY = 0;
    this->width = width;
    this->height = height;
    /*for(int i=0; i < this->getWidth(); i++)
    {
        for(int j=0; j < this->getHeight(); j++)
        {
            this->pixels[( (i + offsetX) + (offsetY + j) * this->width) * 3 + RED] = 0;
            this->pixels[( (i + offsetX) + (offsetY + j) * this->width) * 3 + GREEN] = 0;
            this->pixels[( (i + offsetX) + (offsetY + j) * this->width) * 3 + BLUE] = 0;
        }
    }*/

}

int Image::getWidth() const
{
    return this->width;
}

int Image::getHeight() const
{
    return this->height;
}

uint8_t* Image::getPixels() const
{
    return this->pixels;
}

/*uint8_t* Image::rgb_array()
{
    printf("go\n");
    uint8_t* rgb_image;
    rgb_image = (uint8_t*) malloc(this->width*this->height*3);


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
    printf("terminer\n");

    return rgb_image;
}*/

uint8_t& Image::operator() (int x, int y, int color){
    return this->pixels[( (x + offsetX) + (offsetY + y) * this->width) * 4 + color];
}

void const Image::save(char* filename) const
{
    stbi_write_png(filename, this->getWidth(), this->getHeight(), 4, this->getPixels(), this->getWidth()*4);
}

void Image::crop(int top, int bottom, int left, int right)
{
    int tempWidth = right - left;
    int tempHeight = bottom - top;

    this->offsetX = left;
    this->offsetY = top;

    this->width = tempWidth;
    this->height = tempHeight;
}

Image::~Image()
{
    //dtor
}
