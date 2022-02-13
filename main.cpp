#include <stdint.h>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "lib/stb/stb_image.h"
#include "lib/stb/stb_image_write.h"

int main() {
    int width, height, bpp;

    uint8_t* rgb_image = stbi_load("ciel.jpg", &width, &height, &bpp, 3);

    printf("Width : %d - Height : %d - %d", width, height, bpp);

    for(int i=0; i < width * height * 3; i++)
    {

        //printf("%d ", rgb_image[i]);
        if(i%3 == 0)
        {
            rgb_image[i] = (rgb_image[i] - 50)%255;
        }
    }

    stbi_write_png("image.jpg", width, height, 3, rgb_image, width*3);

    stbi_image_free(rgb_image);

    return 0;
}
