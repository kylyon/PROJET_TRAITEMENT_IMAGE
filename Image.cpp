#include "Image.h"
#include "Pixel.h"
#include <vector>
#include <string>
#include <bits/stdc++.h>

using std::vector;
using std::string;
using namespace std;

Image::Image(char* filename)
{
    this->pixels = stbi_load(filename, &this->width, &this->height, &this->bpp, 4);
}

Image::Image(string filename)
{
    this->pixels = stbi_load(filename.c_str(), &this->width, &this->height, &this->bpp, 4);
}

Image::Image(int height, int width)
{
    this->pixels = (uint8_t*) malloc(width*height*4);
    this->width = width;
    this->height = height;
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

Image Image::mask(Image background, int seuil)
{
    Image cop = Image(this->getHeight(), this->getWidth());

    for(int i=0; i < cop.getWidth(); i++) {
        for(int j=0; j < cop.getHeight(); j++) {
            float similarity = abs(this->pixels[( i + j * this->width) * 4 + RED] - background(i,j,RED)) + abs(this->pixels[( i + j * this->width) * 4 + GREEN] - background(i,j,GREEN)) + abs(this->pixels[( i + j * this->width) * 4 + BLUE] - background(i,j,BLUE)) + abs(this->pixels[( i + j * this->width) * 4 + ALPHA] - background(i,j,ALPHA));
            if(similarity < seuil) {
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

int Image::getCenter(string cen) {
    int xmax = 0, xmin = this->getWidth(), ymin = this->getHeight(), ymax = 0;

    for(int y = 0; y < this->getHeight(); y++) {
        for(int x = 0; x < this->getWidth(); x++) {
            if(!(this->pixels[( x + y * this->width) * 4 + RED] == 0 && this->pixels[( x + y * this->width) * 4 + GREEN] == 0 && this->pixels[( x + y * this->width) * 4 + BLUE] == 0 && this->pixels[( x + y * this->width) * 4 + ALPHA] == 0)) {
                if(x > xmax) {
                    xmax = x;
                }
                if(x < xmin) {
                    xmin = x;
                }
                if(y > ymax) {
                    ymax = y;
                }
                if(y < ymin) {
                    ymin = y;
                }
            }
        }
    }

    if(cen == "x") {
        return int((xmin+xmax)/2);
    } else if(cen == "y") {
        return int((ymin+ymax)/2);
    }
}

Image Image::medianBlur(int radius)
{
    Image cop = Image(this->height,this->width);
    for(int i = 0; i<this->width; i++){
         for(int j = 0; j<this->height; j++){
            int nbVoisin = 0;
            vector<uint8_t> medR = vector<uint8_t>();
            vector<uint8_t> medG = vector<uint8_t>();
            vector<uint8_t> medB = vector<uint8_t>();
            int minX = i - radius >= 0 ? i - radius : 0;
            int maxX = i + radius + 1 <= this->width ? i + radius + 1 : this->width;
            int minY = j - radius >= 0 ? j - radius : 0;
            int maxY =  j + radius + 1 <= this->height ?  j + radius + 1 : this->height;


            for(int x = minX; x < maxX; x++){
                for(int y = minY; y < maxY; y++){
                    medR.push_back( this->pixels[( x + y * this->width) * 4 + RED] );
                    medG.push_back( this->pixels[( x + y * this->width) * 4 + GREEN] );
                    medB.push_back( this->pixels[( x + y * this->width) * 4 + BLUE] );
                }
            }

            sort(medR.begin(), medR.end());
            sort(medG.begin(), medG.end());
            sort(medB.begin(), medB.end());

            cop(i,j,RED) = medR[(int)(medR.size()/2)];
            cop(i,j,GREEN) = medG[(int)(medG.size()/2)];
            cop(i,j,BLUE) = medB[(int)(medB.size()/2)];
            cop(i,j,ALPHA) = 255;
         }
    }
    return cop;
}

Image::~Image()
{
    //dtor
}
