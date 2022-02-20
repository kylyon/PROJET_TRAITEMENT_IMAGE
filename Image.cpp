#include "Image.h"
#include "Pixel.h"
#include <vector>

using std::vector;
using namespace std;

Image::Image(char* filename)
{
    this->pixels = stbi_load(filename, &this->width, &this->height, &this->bpp, 4);
}

Image::Image(int height, int width)
{
    this->pixels = (uint8_t*) malloc(width*height*4);
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
    return this->pixels[( x + y * this->width) * 4 + color];
}

void const Image::save(char* filename) const
{
    stbi_write_png(filename, this->getWidth(), this->getHeight(), 4, this->getPixels(), this->getWidth()*4);
}

void Image::crop(int top, int bottom, int left, int right)
{
    int tempWidth = right - left;
    int tempHeight = bottom - top;

    uint8_t* tempList = (uint8_t*) malloc(tempHeight*tempWidth*4);

    for(int i=0; i < tempWidth; i++)
    {
        for(int j=0; j < tempHeight; j++)
        {
            tempList[( i + j * tempWidth) * 4 + RED] = this->pixels[( (i + left) + (top + j) * this->width) * 4 + RED];
            tempList[( i + j * tempWidth) * 4 + GREEN] = this->pixels[( (i + left) + (top + j) * this->width) * 4 + GREEN];
            tempList[( i + j * tempWidth) * 4 + BLUE] = this->pixels[( (i + left) + (top + j) * this->width) * 4 + BLUE];
            tempList[( i + j * tempWidth) * 4 + ALPHA] = this->pixels[( (i + left) + (top + j) * this->width) * 4 + ALPHA];
        }
    }

    this->pixels = tempList;

    this->width = tempWidth;
    this->height = tempHeight;
}

Image Image::mask(Image background)
{
    Image cop = Image(this->getHeight(), this->getWidth());

    for(int i=0; i < cop.getWidth(); i++) {
        for(int j=0; j < cop.getHeight(); j++) {
            if(this->pixels[( i + j * this->width) * 4 + RED] == background(i,j,RED) && this->pixels[( i + j * this->width) * 4 + GREEN] == background(i,j,GREEN) && this->pixels[( i + j * this->width) * 4 + BLUE] == background(i,j,BLUE) && this->pixels[( i + j * this->width) * 4 + ALPHA] == background(i,j,ALPHA)) {
                cop(i,j,ALPHA) = 0;
                cop(i,j,RED) = 0;
                cop(i,j,GREEN) = 0;
                cop(i,j,BLUE) = 0;
            } else {
                cop(i,j,ALPHA) = this->pixels[( i + j * this->width) * 4 + ALPHA];
                cop(i,j,RED) = this->pixels[( i + j * this->width) * 4 + RED];
                cop(i,j,GREEN) = this->pixels[( i + j * this->width) * 4 + GREEN];
                cop(i,j,BLUE) = this->pixels[( i + j * this->width) * 4 + BLUE];
            }
        }
    }
    return cop;
}

Image::~Image()
{
    //dtor
}
