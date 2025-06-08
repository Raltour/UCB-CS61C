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
	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Error opening file\n");
		return NULL;
	}
	char buff[3];
	fscanf(fp, "%2s", buff);
	if (strcmp(buff, "P3") != 0) {
		printf("Invalid file format\n");
		fclose(fp);
		return NULL;
	}
	int row, col;
	fscanf(fp, "%d %d", &col, &row);
	int maxcolor;
	fscanf(fp, "%d", &maxcolor);

	Image *image =  (Image*)malloc(sizeof(Image));
	if (image == NULL) {
		printf("Error allocating memory\n");
		return NULL;
	}

	image->image = (Color**)malloc(sizeof(Color*) * row);
	if (image->image == NULL) {
		printf("Error allocating memory\n");
		free(image);
		return NULL;
	}

	for(int i = 0; i < row; i++) {
		image->image[i] = (Color*)malloc(sizeof(Color) * col);
		if (image->image[i] == NULL) {
			printf("Error allocating memory\n");
			for (int j = 0; j < i; j++) {
				free(image->image[j]);
			}
			free(image->image);
			free(image);
			return NULL;
		}
	}

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			fscanf(fp, "%u %u %u", 
			       (unsigned int*)&image->image[i][j].R, 
			       (unsigned int*)&image->image[i][j].G, 
			       (unsigned int*)&image->image[i][j].B);
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
	if (image == NULL) {
		printf("Error: Image is NULL\n");
		return;
	}
	//YOUR CODE HERE
	printf("P3\n");
	printf("%d %d\n", image->cols, image->rows);
	printf("255\n");
	for (int i = 0; i < image->rows; i++) {
		int j;
		for (j = 0; j < image->cols; j++) {
			printf("%3d %3d %3d", image->image[i][j].R, image->image[i][j].G, image->image[i][j].B);
			if (j < image->cols - 1) {
				printf("   ");
			} else {
				printf("\n");
			}
		}
	}
}

//Frees an image
void freeImage(Image *image)
{
	//YOUR CODE HERE
	if (image != NULL) {
		if (image->image != NULL) {
			for (int i = 0; i < image->rows; i++) {
				if (image->image[i] != NULL) {
					free(image->image[i]);
				}
			}
			free(image->image);
		}
		free(image);
	}
}
