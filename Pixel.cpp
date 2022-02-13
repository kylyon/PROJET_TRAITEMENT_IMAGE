#include "Pixel.h"

Pixel::Pixel()
{
    this->r = 0;
    this->g = 0;
    this->b = 0;
}

Pixel::Pixel(int r, int g, int b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}

const int Pixel::getRed() const
{
    return this->r;
}

const int Pixel::getGreen() const
{
    return this->g;
}

const int Pixel::getBlue() const
{
    return this->b;
}

const int Pixel::setRed(int r)
{
    this->r = r;
}

const int Pixel::setGreen(int g)
{
    this->g = g;
}

const int Pixel::setBlue(int b)
{
    this->b = b;
}


Pixel::~Pixel()
{
    //dtor
}
