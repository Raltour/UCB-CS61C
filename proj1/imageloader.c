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
		exit(-1);
	}
	int row, col;
	fscanf(fp, "%d %d", &col, &row);
	int maxcolor;
	fscanf(fp, "%d", &maxcolor);

	Image *image =  (Image*)malloc(sizeof(Image));
	if (image == NULL) {
		printf("Error allocating memory\n");
		exit(-1);
	}

	image->image = (Color**)malloc(sizeof(Color*) * row * col);
	if (image->image == NULL) {
		printf("Error allocating memory\n");
		free(image);
		return NULL;
	}

	for (int i = 0; i < row * col; i++) {
		image->image[i] = (Color*)malloc(sizeof(Color));
		if (image->image[i] == NULL) {
			printf("Error allocating memory\n");
			for (int j = 0; j < i; j++) {
				free(image->image[j]);
			}
			free(image->image);
			free(image);
			exit(-1);
		}
	}

	for (int i = 0; i < row * col; i++) {
		unsigned int r, g, b;
		fscanf(fp, "%u %u %u", &r, &g, &b);
		image->image[i]->R = (uint8_t) r;
		image->image[i]->G = (uint8_t) g;
		image->image[i]->B = (uint8_t) b;
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
		for (int j = 0; j < image->cols; j++) {
			printf("%3d %3d %3d", image->image[i * image->cols + j]->R,
				image->image[i * image->cols + j]->G, image->image[i * image->cols + j]->B);
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
			for (int i = 0; i < image->rows * image->cols; i++) {
				if (image->image[i] != NULL) {
					free(image->image[i]);
				}
			}
			free(image->image);
		}
		free(image);
	}
}
