#include <stdint.h>

#include "Image.cpp"
#include "Pixel.cpp"

#include <vector>
#include <bits/stdc++.h>

using std::vector;
using namespace std;

Image getBackground(vector<Image> images);

int main() {
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

    Image test = getBackground(images);
    test.save("back.jpg");

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
    //im.crop(0,100,0,100);
    im.save("image.jpg");

    stbi_image_free(im.getPixels());

    return 0;
}

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
