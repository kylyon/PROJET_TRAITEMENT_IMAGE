#include <stdint.h>
#include "Image.h"
#include "Pixel.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "lib/stb/stb_image.h"
#include "lib/stb/stb_image_write.h"

int main() {
    Image im = Image("ciel.jpg");

    printf("Width : %d - Height : %d", im.getWidth(), im.getHeight());

    for(int i=0; i < im.getWidth() * im.getHeight() * 3; i++)
    {

        //printf("%d % 3  = %d \n", i, i%3);
        if(i%3 == 2)
        {
            im.getPixels()[i].setBlue(0);
        }
    }

    stbi_write_png("image.jpg", im.getWidth(), im.getHeight(), 3, im.rgb_array(), im.getHeight()*3);

    stbi_image_free(im.getPixels());

    return 0;
}
