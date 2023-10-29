#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _pixel {
    int red;
    int green;
    int blue;
} Pixel;

typedef struct _imagePPM {
    char magic[3];  // magic identifier, "P3" for PPM
    int width;      // number of columns
    int height;     // number of rows
    int max_value;  // maximum intensity of RGB components
    Pixel **pixels; // the actual color pixel data
} ImagePPM;


// Priyanshu Sethi:- Reading the Image file and storing it into a 2-d matrix
ImagePPM *readPPM(char *filename){
    ImagePPM *pImagePPM=malloc(sizeof(ImagePPM));
    FILE *fp = fopen(filename, "r");
    if(fp==NULL){
        return NULL;
     }
    fscanf(fp,"%s",pImagePPM->magic);
    fscanf(fp,"%d",&pImagePPM->width);
    fscanf(fp,"%d",&pImagePPM->height);
    fscanf(fp,"%d",&pImagePPM->max_value);
    pImagePPM->pixels = malloc(sizeof(Pixel *) * pImagePPM->height);

    for(int i = 0;i<pImagePPM->height;i++){
        pImagePPM->pixels[i] = malloc(sizeof(Pixel) * pImagePPM->width);
        }
    for(int i=0;i<pImagePPM->height;i++){
        for(int j=0;j<pImagePPM->width;j++){
            fscanf(fp, "%d", &pImagePPM->pixels[i][j].red);
            fscanf(fp, "%d", &pImagePPM->pixels[i][j].green);
            fscanf(fp, "%d", &pImagePPM->pixels[i][j].blue);
        }
     }
    fclose(fp);
    return pImagePPM;
    }


// Priyanshu Sethi:- Printing out the 2d matrix to a ppm file
int writePPM(ImagePPM *pImagePPM, char *filename){
    FILE *fp = fopen(filename, "w");
    if(fp==NULL){
        return 0;
        }
    fprintf(fp,"%s\n",pImagePPM->magic);
    fprintf(fp,"%d %d\n",pImagePPM->width,pImagePPM->height);
    fprintf(fp,"%d\n",pImagePPM->max_value);
    for(int i=0;i<pImagePPM->height;i++){
            for(int j=0;j<pImagePPM->width;j++){
                fprintf(fp, "%4d", pImagePPM->pixels[i][j].red);
                fprintf(fp, "%4d", pImagePPM->pixels[i][j].green);
                fprintf(fp, "%4d", pImagePPM->pixels[i][j].blue);
            }
            fprintf(fp, "\n");
        }
        fclose(fp);
        return 1;
}
// Priyanshu Sethi:- Rotating the image (2d matrix) by 90 degrees clockwise
ImagePPM *rotatePPM(ImagePPM *pImagePPM){

    ImagePPM *tempmatrix=malloc(sizeof(tempmatrix));
    strcpy(tempmatrix->magic,pImagePPM->magic);
    tempmatrix->width = pImagePPM->height;
    tempmatrix->height=pImagePPM->width;
    tempmatrix->max_value=pImagePPM->max_value;
    tempmatrix->pixels = malloc(sizeof(Pixel *) * tempmatrix->height);
    for(int i = 0;i<tempmatrix->height;i++){
            tempmatrix->pixels[i] = malloc(sizeof(Pixel) * tempmatrix->width);
        }
    for(int i=0;i<pImagePPM->height;i++){
            for(int j=0;j<pImagePPM->width;j++){
                tempmatrix->pixels[j][tempmatrix->width - 1 - i] = pImagePPM->pixels[i][j];
            }
        }
    return tempmatrix;
}
// Priyanshu Sethi:- Flip the 2d matrix 
ImagePPM *flipPPM(ImagePPM *pImagePPM){
    ImagePPM *tempmatrix=malloc(sizeof(tempmatrix));
    strcpy(tempmatrix->magic,pImagePPM->magic);
    tempmatrix->width = pImagePPM->width;
    tempmatrix->height=pImagePPM->height;
    tempmatrix->max_value=pImagePPM->max_value;
    tempmatrix->pixels = malloc(sizeof(Pixel *) * tempmatrix->height);
    for(int i = 0;i<tempmatrix->height;i++){
            tempmatrix->pixels[i] = malloc(sizeof(Pixel) * tempmatrix->width);
        }
    for(int i=0;i<pImagePPM->height;i++){
            for(int j=0;j<pImagePPM->width;j++){
                tempmatrix->pixels[i][tempmatrix->width-1-j] = pImagePPM->pixels[i][j];
            }
        }
        return tempmatrix;
}
// PRiyanshu Sethi:- Enlarge the 2-d matrix by 2x
ImagePPM *enlargePPM(ImagePPM *pImagePPM){
    ImagePPM *tempmatrix = malloc(sizeof(tempmatrix));
    strcpy(tempmatrix->magic,pImagePPM->magic);
    tempmatrix->width = (pImagePPM->width)*2;
    tempmatrix->height=(pImagePPM->height)*2;
    tempmatrix->max_value=pImagePPM->max_value;
    tempmatrix->pixels = malloc(sizeof(Pixel *) * tempmatrix->height);
    for(int i = 0;i<tempmatrix->height;i++){
            tempmatrix->pixels[i] = malloc(sizeof(Pixel) * tempmatrix->width);
        }
    for(int i=0;i<pImagePPM->height;i++){
            for(int j=0;j<pImagePPM->width;j++){
                tempmatrix->pixels[2*i][2*j] = pImagePPM->pixels[i][j];
                tempmatrix->pixels[2*i+1][2*j] = pImagePPM->pixels[i][j];
                tempmatrix->pixels[2*i][2*j+1] = pImagePPM->pixels[i][j];
                tempmatrix->pixels[2*i+1][2*j+1] = pImagePPM->pixels[i][j];
            }
        }
    return tempmatrix;
}
// Priyanshu Sethi:- Shrink the 2-d matrix by 1/2x
ImagePPM *shrinkPPM(ImagePPM *pImagePPM){
    ImagePPM *pImagePPM2 = (ImagePPM *)malloc(sizeof(ImagePPM));
    strcpy(pImagePPM2->magic, pImagePPM->magic);
    pImagePPM2->height = (pImagePPM->height) / 2;
    pImagePPM2->width = (pImagePPM->width) / 2;
    pImagePPM2->max_value = pImagePPM->max_value;

    pImagePPM2->pixels = (Pixel **)malloc(sizeof(Pixel *) * pImagePPM2->height);

    for(int i = 0; i < pImagePPM2->height ; i++) {
        pImagePPM2->pixels[i] = (Pixel *)malloc(sizeof(Pixel) * pImagePPM2->width);
    }

    for(int i = 0; i < pImagePPM2->height; i++) {
        for(int j = 0; j < pImagePPM2->width; j++) {
            pImagePPM2->pixels[i][j].red = (int)round( (double) (pImagePPM->pixels[2 * i][2 * j].red + pImagePPM->pixels[2 * i + 1][2 * j].red + pImagePPM->pixels[2 * i][2 * j + 1].red + pImagePPM->pixels[2 * i + 1][2 * j + 1].red) / 4);
            pImagePPM2->pixels[i][j].green = (int)round( (double) (pImagePPM->pixels[2 * i][2 * j].green + pImagePPM->pixels[2 * i + 1][2 * j].green + pImagePPM->pixels[2 * i][2 * j + 1].green + pImagePPM->pixels[2 * i + 1][2 * j + 1].green) / 4);
            pImagePPM2->pixels[i][j].blue =  (int)round( (double) (pImagePPM->pixels[2 * i][2 * j].blue + pImagePPM->pixels[2 * i + 1][2 * j].blue + pImagePPM->pixels[2 * i][2 * j + 1].blue + pImagePPM->pixels[2 * i + 1][2 * j + 1].blue) / 4);
        }
    }

    return pImagePPM2;
}
// Priyanshu Sethi:- Invert the 2-d matrix 
ImagePPM *invertPPM(ImagePPM *pImagePPM){
    ImagePPM *tempmatrix=malloc(sizeof(tempmatrix));
    strcpy(tempmatrix->magic,pImagePPM->magic);
    tempmatrix->width = pImagePPM->width;
    tempmatrix->height=pImagePPM->height;
    tempmatrix->max_value=pImagePPM->max_value;
    tempmatrix->pixels = malloc(sizeof(Pixel *) * tempmatrix->height);
    for(int i = 0;i<tempmatrix->height;i++){
            tempmatrix->pixels[i] = malloc(sizeof(Pixel) * tempmatrix->width);
        }
    for(int i=0;i<pImagePPM->height;i++){
            for(int j=0;j<pImagePPM->width;j++){
                tempmatrix->pixels[i][j].red = (pImagePPM->max_value)-(pImagePPM->pixels[i][j].red);
                tempmatrix->pixels[i][j].green = (pImagePPM->max_value)-(pImagePPM->pixels[i][j].green);
                tempmatrix->pixels[i][j].blue = (pImagePPM->max_value)-(pImagePPM->pixels[i][j].blue);
            }
        }
        return tempmatrix;
}
// crop the 2-d matrix
ImagePPM *cropPPM(ImagePPM *pImagePPM, int r1, int c1, int r2, int c2){
    // finish this
    int cropWidth = abs(c2 - c1) + 1;
    int cropHeight = abs(r2 - r1) + 1;
    ImagePPM *croppedImage = (ImagePPM *)malloc(sizeof(ImagePPM));
    strcpy(croppedImage->magic, pImagePPM->magic);
    croppedImage->width = cropWidth;
    croppedImage->height = cropHeight;
    croppedImage->max_value = pImagePPM->max_value;

    croppedImage->pixels = (Pixel **)malloc(sizeof(Pixel *) * cropHeight);
    for (int i = 0; i < cropHeight; i++) {
        croppedImage->pixels[i] = (Pixel *)malloc(sizeof(Pixel) * cropWidth);
    }
    int startRow = r1 < r2 ? r1 : r2;
    int startCol = c1 < c2 ? c1 : c2;

    for (int i = 0; i < cropHeight; i++) {
        for (int j = 0; j < cropWidth; j++) {
            croppedImage->pixels[i][j] = pImagePPM->pixels[startRow + i][startCol + j];
        }
    }

    return croppedImage;
}
// free space for 2-d matrix
void freeSpacePPM(ImagePPM *pImagePPM){
    for (int i = 0; i < pImagePPM->height; i++) {
        free(pImagePPM->pixels[i]); 
    }
    free(pImagePPM->pixels);

    free(pImagePPM);
    }