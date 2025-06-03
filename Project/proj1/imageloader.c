/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-15
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"

//Opens a .ppm P3 image file, and constructs an Image object. 
//You may find the function fscanf useful.
//Make sure that you close the file with fclose before returning.
Image *readData(char *filename) 
{
	//YOUR CODE HERE
	Image *image =  (Image*)malloc(sizeof(Image));
	if (image == NULL) {
		printf("Error allocating memory\n");
		return NULL;
	}

	FILE *fp = fopen(filename, "r");
	char buff[3];
	fscanf(fp, "%s", buff);
	int row, col;
	fscanf(fp, "%d %d", &col, &row);
	int maxcolor;
	fscanf(fp, "%d", &maxcolor);

	image->image = (Color**)malloc(sizeof(Color*) * row);
	for(int i = 0; i < row; i++) {
		image->image[i] = (Color*)malloc(sizeof(Color) * col);
	}
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			fscanf(fp, "%d %d %d", image->image[i][j].R, image->image[i][j].G, image->image[i][j].B);
		}
	}
	image->cols = col;
	image->rows = row;
	fclose(fp);
	return image;
}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
	//YOUR CODE HERE
	printf("P3\n");
	printf("%d %d\n", image->cols, image->rows);
	printf("255\n");
	for (int i = 0; i < image->rows; i++) {
		int j;
		for (j = 0; j < image->cols - 1; j++) {
			printf("%3d %3d %3d   ", image->image[i][j].R, image->image[i][j].G, image->image[i][j].B);
		}
		printf("%3d %3d %3d", image->image[i][j].R, image->image[i][j].G, image->image[i][j].B);
		printf("\n");
	}
}

//Frees an image
void freeImage(Image *image)
{
	//YOUR CODE HERE
	for (int i = 0; i < image->rows; i++) {
		free(image->image[i]);
	}
	free(image->image);
	free(image);
}