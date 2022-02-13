#ifndef PIXEL_H
#define PIXEL_H


class Pixel
{
    public:
        Pixel();
        Pixel(int r, int g, int b);
        const int getRed() const;
        const int getGreen() const;
        const int getBlue() const;
        const int setRed(int r);
        const int setGreen(int g);
        const int setBlue(int b);
        virtual ~Pixel();

    protected:

    private:
        int r, g, b;
};

#endif // PIXEL_H
