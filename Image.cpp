#include "Image.h"
#include "Pixel.h"
#include <vector>

using std::vector;
using namespace std;

Image::Image(char* filename)
{
    this->pixels = stbi_load("ciel.jpg", &this->width, &this->height, &this->bpp, 3);
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
    return this->pixels[(x + y * this->width) * 3 + color];
}

Image::~Image()
{
    //dtor
}
