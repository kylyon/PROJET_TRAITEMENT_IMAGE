#include <stdint.h>

#include "Image.cpp"
#include "Pixel.cpp"

using namespace std;

int main() {
    Image im = Image("ciel.jpg");

    printf("Width : %d - Height : %d", im.getWidth(), im.getHeight());

    for(int i=0; i < 30; i++)
    {
        for(int j=0; j < 30; j++)
        {
            //printf("%d - %d", i, im.getPixels()[i].getBlue());
            im(i,j, RED) -= 50;
            //printf(" - %d\n", im.getPixels()[i].getBlue());
        }

    }

    stbi_write_png("image.jpg", im.getWidth(), im.getHeight(), 3, im.getPixels(), im.getHeight()*3);

    stbi_image_free(im.getPixels());

    return 0;
}
