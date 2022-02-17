#include <stdint.h>

#include "Image.cpp"
#include "Pixel.cpp"

#include <vector>
#include <bits/stdc++.h>

using std::vector;
using namespace std;

Image getBackground(vector<Image> images);

int main(int argc, char *argv[]) {

    printf("%s\n", argv[1]);
    vector<Image> images = vector<Image>();

    Image im = Image("Image/image1.jpg");
    Image im1 = Image("Image/image2.jpg");
    Image im2 = Image("Image/image3.jpg");
    Image im3 = Image("Image/image4.jpg");
    Image im4 = Image("Image/image5.jpg");
    Image im5 = Image("Image/image6.jpg");
    Image im6 = Image("Image/image7.jpg");
    Image im7 = Image("Image/image8.jpg");

    images.push_back(im);
    images.push_back(im1);
    images.push_back(im2);
    images.push_back(im3);
    images.push_back(im4);
    images.push_back(im5);
    images.push_back(im6);
    images.push_back(im7);

<<<<<<< Updated upstream
    Image test = getBackground(images);
    test.save("back.jpg");

    Image cop = im.mask(test);
    cop.save("mask.png");
=======
    Image result = setResult(background, images.size(), 3);
    result.save("Result/resultat.png");
>>>>>>> Stashed changes

    printf("Width : %d - Height : %d", im.getWidth(), im.getHeight());

    /*for(int i=0; i < 30; i++)
    {
        for(int j=0; j < 30; j++)
        {
            //printf("%d - %d", i, im.getPixels()[i].getBlue());
            im(i,j, RED) -= 50;
            //printf(" - %d\n", im.getPixels()[i].getBlue());
        }

    }
    //im.crop(0,100,0,100);
    im.save("image.jpg");*/

    stbi_image_free(im.getPixels());

    return 0;
}

<<<<<<< Updated upstream
=======
Image setResult(Image background, int sizes, int saut) {
    Image result = background;
    vector<Image> masks = vector<Image>();
    for(int i = 0; i < sizes; i++) {
        string path = "Result/mask";
        path.append(to_string(i));
        path.append(".png");
        masks.push_back(Image(&path[0]));
    }
    // Liste background
    float opacity = 0;
    float stepOpacity = 1.0f / (masks.size()/saut);
    for(int i = 0; i < masks.size(); i+=saut) {
        printf("test %d \n", i);
        for(int x=0; x < result.getWidth(); x++) {
            for(int y = 0; y < result.getHeight(); y++) {
                if(masks[i](x, y, RED) == 0 && masks[i](x, y, GREEN) == 0 && masks[i](x, y, BLUE) == 0 && masks[i](x, y, ALPHA) == 0) {
                } else {
                    result(x, y, RED) = abs((int) masks[i](x, y, RED) - (int)((masks[i](x, y, RED) - result(x, y, RED)) * opacity));
                    result(x, y, GREEN) = abs((int) masks[i](x, y, GREEN) - (int)((masks[i](x, y, GREEN) - result(x, y, GREEN)) * opacity));
                    result(x, y, BLUE) = abs((int) masks[i](x, y, BLUE) - (int)((masks[i](x, y, BLUE) - result(x, y, BLUE)) * opacity));
                    result(x, y, ALPHA) = 255;

                }
            }
        }
        opacity += stepOpacity;
    }
    // Check par rapport au saut quel mask faire, for par rapport a masks.size avec un i + = saut a chaque fin de boucle
    return result;
}

>>>>>>> Stashed changes
Image getBackground(vector<Image> images)
{

    Image im = Image(images[0].getHeight(), images[0].getWidth());
    printf("%d %d %d %d \n", im(0,0,RED), im(0,0,GREEN),im(0,0,BLUE), im(0,0,ALPHA));

    for(int i=0; i < im.getWidth(); i++)
    {
        for(int j=0; j < im.getHeight(); j++)
        {
            vector<int> moyR = vector<int>();
            vector<int> moyG = vector<int>();
            vector<int> moyB = vector<int>();


            for(int k=0; k < images.size(); k++){
                moyR.push_back(images[k](i,j,RED));
                moyG.push_back(images[k](i,j,GREEN));
                moyB.push_back(images[k](i,j,BLUE));
            }

            sort(moyR.begin(), moyR.end());
            sort(moyG.begin(), moyG.end());
            sort(moyB.begin(), moyB.end());

            int medR = moyR[(int)images.size()/2];
            int medG = moyG[(int)images.size()/2];
            int medB = moyB[(int)images.size()/2];

            im(i,j,RED) = medR;
            im(i,j,GREEN) = medG;
            im(i,j,BLUE) = medB;
            im(i,j,ALPHA) = 255;

        }

    }

    return im;
}
