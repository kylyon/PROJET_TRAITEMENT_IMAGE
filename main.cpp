#include <stdint.h>
#include <string>

#include "Image.cpp"
#include "Pixel.cpp"

#include <vector>
#include <bits/stdc++.h>
#include <string>
#include <sstream>

#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

using std::vector;
using std::string;
using namespace std;

Image getBackground(vector<Image> images, bool verbose);
Image setResult(Image background, vector<Image> masks, int sizes, string mode, int value);
vector<Image> normalize(vector<Image> images);
vector<Image> getMasks(vector<Image> images, Image background, bool verbose);
int getResultPixel(Image background, Image mask, int x, int y, int channel, string fading, float opacity);

char* path = "Image/vertical";
bool verbose = false;
string fading = "normal";
string mode = "normal";
int saut = 1;




vector<Image> getImagesFromDisk(const char *arg)
{
    DIR *dirp;
    struct dirent *dp;


    if ((dirp = opendir(arg)) == NULL) {
        perror("couldn't open arg");
        return vector<Image>();
    }
    printf("open %s\n", arg);

    vector<Image> images = vector<Image>();
    do {
        errno = 0;
        if ((dp = readdir(dirp)) != NULL) {
            if(strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0){
                char temp[100];   // array to hold the result.

                strcpy(temp,arg); // copy string one into the result.
                string str = arg;
                char lastChar = str.back();
                if(lastChar != '/')
                {
                    strcat(temp,"/");
                }
                strcat(temp,dp->d_name);

                string result = temp;
                if(result.find(".jpg") || result.find(".jpeg") || result.find(".png"))
                {
                    printf("- %s\n", temp);

                    Image im = Image(result);
                    images.push_back(im);
                }
            }
        }
    } while (dp != NULL);

    return images;
}

int main(int argc, char *argv[]) {


    if(argc != 6 && argc != 2)
    {
        printf("Veuillez renseigner les 5 parametres :\n");
        printf("    path : le chemin vers le dossier contenant les images a traiter\n");
        printf("    verbose : true ou false\n");
        printf("    fading : normal ou fading ou reverse\n");
        printf("    mode : normal ou step ou distance\n");
        printf("    mode value : valeur pour le mode choisi (Ex : mode value = 2 avec le mode step veut dire un pas de 2)\n");
        return 0;
    }

    vector<string> all_args;

    if (argc > 1) {
        all_args.assign(argv, argv + argc);
    }


    if(argc > 1)
    {
        path = argv[1];
        if(argc > 2)
        {
            std::stringstream ssVerbose(all_args[2]);
            verbose = all_args[2] == "true" ? 1: 0;;


            if(!(ssVerbose >> std::boolalpha >> verbose)) {
                printf("L'argument verbose doit avoir comme valeur true or false\n");
            }

            std::cout << std::boolalpha;
            std::cout<<verbose<<"\n";

            fading = all_args[3];
            mode = all_args[4];
            saut = stoi(all_args[5]);
        }
    }


    vector<Image> images = getImagesFromDisk(path);
    vector<Image> blur = vector<Image>();

    for(int i = 0; i < images.size(); i++)
    {
        Image temp = images[i].medianBlur(1);
        string path = "Result/blur";
        path.append(to_string(i));
        path.append(".png");
        temp.save(&path[0]);
        blur.push_back(temp);
    }

    if(!images.size())
    {
        printf("No images found");
        return 0;
    }

    Image background = getBackground(blur, verbose);

    vector<Image> masks = getMasks(blur,background, verbose);

    Image result = setResult(background, masks, blur.size(), mode, saut);
    result.save("Result/resultat.png");

    //stbi_image_free(im.getPixels());

    return 0;
}

Image setResult(Image background, vector<Image> masks, int sizes, string mode, int value) {
    Image result = background;
    int saut = mode=="step"?value : 1;
    int start = 0;

    float opacity = 0;
    float stepOpacity = 1.0f / (masks.size()/saut);

    cout<<mode<<" mode";

    // Liste background
    if(mode == "distance") {
        start = 1;
        for(int x=0; x < result.getWidth(); x++) {
            for(int y = 0; y < result.getHeight(); y++) {
                if(!(masks[0](x, y, RED) == 0 && masks[0](x, y, GREEN) == 0 && masks[0](x, y, BLUE) == 0 && masks[0](x, y, ALPHA) == 0)) {
                    result(x, y, RED) = getResultPixel(result, masks[0], x, y, RED, fading, opacity);
                    result(x, y, GREEN) = getResultPixel(result, masks[0], x, y, GREEN, fading, opacity);
                    result(x, y, BLUE) = getResultPixel(result, masks[0], x, y, BLUE, fading, opacity);
                    result(x, y, ALPHA) = masks[0](x, y, ALPHA);
                }
            }
        }
    }
    for(int i = start; i < masks.size(); i+=saut) {
        int v = 0;
        if(mode == "distance")
        {
            int xcenterV = masks[v].getCenter("x");
            int xcenterI = masks[i].getCenter("x");
            int ycenterV = masks[v].getCenter("y");
            int ycenterI = masks[i].getCenter("y");
            if(abs(sqrt(pow((xcenterV - xcenterI), 2) + pow((ycenterV - ycenterI), 2))) > value) {
                continue;
            }
        }
        for(int x=0; x < result.getWidth(); x++) {
            for(int y = 0; y < result.getHeight(); y++) {
                if(!(masks[i](x, y, RED) == 0 && masks[i](x, y, GREEN) == 0 && masks[i](x, y, BLUE) == 0 && masks[i](x, y, ALPHA) == 0)) {
                    result(x, y, RED) = getResultPixel(result, masks[i], x, y, RED, fading, opacity);
                    result(x, y, GREEN) = getResultPixel(result, masks[i], x, y, GREEN, fading, opacity);
                    result(x, y, BLUE) = getResultPixel(result, masks[i], x, y, BLUE, fading, opacity);
                    result(x, y, ALPHA) = masks[i](x, y, ALPHA);
                }
            }
        }
        opacity += stepOpacity;
        if(mode == "distance")
        {
            v = i;
        }
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
        Image cop = images[i].mask(background, 50);
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
