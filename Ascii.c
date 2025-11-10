#include <stdio.h>
#include <stdlib.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <string.h>
#include <unistd.h>
#define BrightnessVal 50
typedef struct Image{
    int Width;
    int Height;
}Image;
Image image;
  const char Characters[] = " .-=+*x#$X@";
int Height , Width , PixelSize;
int CharacterLen = sizeof(Characters) - 1;
int Brightness(int x){
    x += BrightnessVal;
    if(x > 255){x = 255;}
    return x ;
}
void CreateImage(unsigned char *ImageData){
    printf("\x1b[2J");
    unsigned char *Pixels = ImageData;
    for(int i = 0 ; i < image.Height ; i++){
      for(int j = 0 ; j < image.Width ; j++){
       unsigned char r = *Pixels++;
       unsigned char g = *Pixels++;
       unsigned char b = *Pixels++;
       if(PixelSize >= 4){unsigned char a = *Pixels++;}
       float Average = (r + g + b) / 3.0;
       int CharIndex = (int)((Average / 255) * CharacterLen - 1);
       printf("\33[38;2;%d;%d;%dm%c" , r , g , b ,Characters[CharIndex]);
      // putchar(Characters[CharIndex]);
       usleep(100);
      }
      putchar('\n');
    }
}
void Resize(unsigned char *ImageData, int OriginalHeight , int OriginalWidth , int Block){
    unsigned char *Pixels = ImageData;
    image.Height = (int)(OriginalHeight/(Block*2));
    image.Width = (int)(OriginalWidth/Block);
    unsigned char *NewImage = malloc(image.Width * image.Height * PixelSize);
    for(int H = 0 ; H < image.Height ; H++){
      for(int W = 0 ; W < image.Width ; W++){
        long Ravg = 0 , Gavg = 0 , Bavg = 0;
        for(int i = 0 ; i < Block * 2 ; i++ ){
          for(int j = 0 ; j < Block ; j++){
            int srcx = W * Block + j;
            int srcy = H * (Block*2) + i;
            int PixelIndex = (srcy * OriginalWidth + srcx) * PixelSize;
            unsigned char r = ImageData[PixelIndex + 0];
            unsigned char g = ImageData[PixelIndex + 1];
            unsigned char b = ImageData[PixelIndex + 2];
            if(PixelSize >= 4){unsigned char a = ImageData[PixelIndex + 3];}
            Ravg += r;
            Gavg += g;
            Bavg += b;

          }
        }
        Ravg /= Block * (2*Block);
        Gavg /= Block * (2*Block);
        Bavg /= Block * (2*Block);
        Ravg = Brightness(Ravg);
        Gavg = Brightness(Gavg);
        Bavg = Brightness(Bavg);
      int index = (H * image.Width + W) * PixelSize;
      NewImage[index + 0] = Ravg;
      NewImage[index + 1] = Gavg;
      NewImage[index + 2] = Bavg;
    }


    }

    CreateImage(NewImage);
    free(NewImage);
}
  


int main(int argc , char *argv[]){
unsigned char *ImageData = stbi_load(argv[1] , &Width , &Height , &PixelSize , 0); 
int Down;
while (1) {
  printf("By what factor do you want to downscale you picture?\n");
  scanf("%d" , &Down);
  if(Down > 0 && Down <= 1000){break;}
}
  if(ImageData){
    Resize(ImageData, Height, Width , Down);
//    CreateImage(ImageData);
  }
  else{
    printf("is this working?");
    printf("Failed to load image %s\n" , argv[1]);
  }


  stbi_image_free(ImageData);
  return 0;
}
