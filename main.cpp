#include <stdint.h>
#include <string>

#include "Image.cpp"
#include "Pixel.cpp"

#include <vector>
#include <bits/stdc++.h>
#include <string>
#include <sstream>

using std::vector;
using std::string;
using namespace std;

Image getBackground(vector<Image> images, bool verbose);
Image setResult(Image background, vector<Image> masks, int sizes, int saut);
vector<Image> normalize(vector<Image> images);
vector<Image> getMasks(vector<Image> images, Image background, bool verbose);
int getResultPixel(Image background, Image mask, int x, int y, int channel, string fading, float opacity);

bool verbose = false;
string fading = "normal";
string mode = "normal";
int saut = 1;

int main(int argc, char *argv[]) {
    if(argc != 5 && argc != 1)
    {
        printf("Veuillez renseigner les 3 parametres :\n");
        printf("    verbose : true ou false\n");
        printf("    fading : normal ou fading ou reverse\n");
        printf("    mode : normal ou step ou distance\n");
        printf("    mode value : valeur pour le mode choisi (Ex : mode value = 2 avec le mode step veut dire un pas de 2\n");
        return 0;
    }

    vector<string> all_args;

    if (argc > 1) {
        all_args.assign(argv, argv + argc);
    }


    if(argc != 1)
    {
        std::stringstream ssVerbose(all_args[1]);
        bool verbose;


        if(!(ssVerbose >> std::boolalpha >> verbose)) {
            printf("L'argument verbose doit avoir comme valeur true or false\n");
        }

        fading = all_args[2];
        mode = all_args[3];
        saut = stoi(all_args[4]);
    }




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

    printf("Saut : %d\n", saut);
    Image background = getBackground(images, verbose);

    vector<Image> masks = getMasks(images,background, verbose);

    Image result = setResult(background,masks, images.size(), saut);
    result.save("Result/resultat.png");


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
    im.crop(0,100,0,100);
    im.save("image.jpg");
    printf("Width : %d - Height : %d", im.getWidth(), im.getHeight());*/

    stbi_image_free(im.getPixels());

    return 0;
}

Image setResult(Image background, vector<Image> masks, int sizes, int saut) {
    Image result = background;
    float opacity = 0;
    float stepOpacity = 1.0f / (masks.size()/saut);

    // Liste background
    for(int i = 0; i < masks.size(); i+=saut) {
        //printf("test %d \n", i);
        for(int x=0; x < result.getWidth(); x++) {
            for(int y = 0; y < result.getHeight(); y++) {
                if(masks[i](x, y, RED) == 0 && masks[i](x, y, GREEN) == 0 && masks[i](x, y, BLUE) == 0 && masks[i](x, y, ALPHA) == 0) {
                } else {
                    result(x, y, RED) = getResultPixel(result, masks[i], x, y, RED, fading, opacity);
                    result(x, y, GREEN) = getResultPixel(result, masks[i], x, y, GREEN, fading, opacity);
                    result(x, y, BLUE) = getResultPixel(result, masks[i], x, y, BLUE, fading, opacity);
                    result(x, y, ALPHA) = masks[i](x, y, ALPHA);
                }
            }
        }
        opacity += stepOpacity;
    }
    // Check par rapport au saut quel mask faire, for par rapport a masks.size avec un i + = saut a chaque fin de boucle
    return result;
}

int getResultPixel(Image result, Image mask, int x, int y, int channel, string fading, float opacity)
{
    if(fading == "fading")
    {
        return abs((int) result(x, y, channel) - (int)((result(x, y, channel) - mask(x, y, channel)) * opacity));
    }
    if(fading == "reverse")
    {
        return abs((int) mask(x, y, channel) - (int)((mask(x, y, channel) - result(x, y, channel)) * opacity));
    }
    return mask(x, y, channel);
}

Image getBackground(vector<Image> images, bool verbose)
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

    if(verbose)
    {
        im.save("Result/backresult.png");
    }

    return im;
}

vector<Image> normalize(vector<Image> images)
{
    int minW = images[0].getWidth();
    int minH = images[0].getHeight();
    int maxW = images[0].getWidth();
    int maxH = images[0].getHeight();

    for(int i=1; i<images.size(); i++){
        minW = minW > images[i].getWidth() ? images[i].getWidth() : minW;
        minH = minH > images[i].getHeight() ? images[i].getHeight() : minH;
        maxW = maxW < images[i].getWidth() ? images[i].getWidth() : maxW;
        maxH = maxH < images[i].getHeight() ? images[i].getHeight() : maxH;
    }

    if(!(minW == maxW && minH == maxH)){
        for(int i=0; i<images.size(); i++){
            images[i].crop(0,minH, 0, minW);
        }
    }

    return images;
}

vector<Image> getMasks(vector<Image> images, Image background,  bool verbose)
{
    vector<Image> masks = vector<Image>();
    for(int i = 0; i < images.size(); i++) {
        Image cop = images[i].mask(background);
        if(verbose)
        {
            string path = "Result/mask";
            path.append(to_string(i));
            path.append(".png");
            cop.save(&path[0]);
        }
        masks.push_back(cop);
    }
    return masks;
}
