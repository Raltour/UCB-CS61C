/************************************************************************
**
** NAME:        steganography.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**				Justin Yokota - Starter Code
**				YOUR NAME HERE
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

//Determines what color the cell at the given row/col should be. This should not affect Image, and should allocate space for a new Color.
Color *evaluateOnePixel(Image *image, int row, int col)
{
	//YOUR CODE HERE
	Color *secret_pixel = (Color*)malloc(sizeof(Color));
	if (!secret_pixel) {
		// Check for malloc failure
		exit(-1);
	}
	if ((image->image[row][col].B & 1) == 0) {
		secret_pixel->R = 0;
		secret_pixel->G = 0;
		secret_pixel->B = 0;
	} else {
		secret_pixel->R = 255;
		secret_pixel->G = 255;
		secret_pixel->B = 255;
	}
	return secret_pixel;
}

//Given an image, creates a new image extracting the LSB of the B channel.
Image *steganography(Image *image)
{
	//YOUR CODE HERE
	Image *secret_image = (Image*)malloc(sizeof(Image));
	if (!secret_image) {
		// Check for malloc failure
		exit(-1);
	}
	secret_image->rows = image->rows;
	secret_image->cols = image->cols;
	secret_image->image = (Color **) malloc(sizeof(Color *) * secret_image->rows);
	if (!secret_image->image) {
		// Check for malloc failure
		free(secret_image);
		exit(-1);
	}
	for (int i = 0; i < secret_image->rows; i++) {
		secret_image->image[i] = (Color *) malloc(sizeof(Color) * secret_image->cols);
		if (!secret_image->image[i]) {
			// Check for malloc failure
			for (int k = 0; k < i; k++) {
				free(secret_image->image[k]);
			}
			free(secret_image->image);
			free(secret_image);
			exit(-1);
		}
		for (int j = 0; j < secret_image->cols; j++) {
			Color *tmp = evaluateOnePixel(image, i, j);
			secret_image->image[i][j] = *tmp;
			free(tmp);
		}
	}
	return secret_image;
}

/*
Loads a file of ppm P3 format from a file, and prints to stdout (e.g. with printf) a new image, 
where each pixel is black if the LSB of the B channel is 0, 
and white if the LSB of the B channel is 1.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a file of ppm P3 format (not necessarily with .ppm file extension).
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!
*/
int main(int argc, char **argv)
{
	//YOUR CODE HERE
	if (argc != 2) {
		// Check for correct number of arguments
		printf("Usage: %s <filename>\n", argv[0]);
		exit(-1);
	}
	Image *image = readData(argv[1]);
	if (!image) {
		// Check for readData failure
		exit(-1);
	}
	Image *secret_image = steganography(image);
	if (!secret_image) {
		// Check for steganography failure
		freeImage(image);
		exit(-1);
	}
	writeData(secret_image);
	freeImage(image);
	freeImage(secret_image);
}
