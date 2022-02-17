#include <stdint.h>
#include <string>

#include "Image.cpp"
#include "Pixel.cpp"

#include <vector>
#include <bits/stdc++.h>

using std::vector;
using namespace std;

Image getBackground(vector<Image> images);

int main() {
    vector<Image> images = vector<Image>();

    Image im = Image("Image/image1.png");
    Image im1 = Image("Image/image2.png");
    Image im2 = Image("Image/image3.png");
    Image im3 = Image("Image/image4.png");
    Image im4 = Image("Image/image5.png");
    Image im5 = Image("Image/image6.png");
    Image im6 = Image("Image/image7.png");
    Image im7 = Image("Image/image8.png");
    Image im8 = Image("Image/image9.png");
    Image im9 = Image("Image/image10.png");
    Image im10 = Image("Image/image11.png");


    images.push_back(im);
    images.push_back(im1);
    images.push_back(im2);
    images.push_back(im3);
    images.push_back(im4);
    images.push_back(im5);
    images.push_back(im6);
    images.push_back(im7);
    images.push_back(im8);
    images.push_back(im9);
    images.push_back(im10);

    Image background = getBackground(images);
    background.save("Result/backresult.png");

    for(int i = 0; i < images.size(); i++) {
        Image cop = images[i].mask(background);
        string path = "Result/mask";
        path.append(to_string(i));
        path.append(".png");
        cop.save(&path[0]);
    }

    // Tout les deux
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
