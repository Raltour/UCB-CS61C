/************************************************************************
**
** NAME:        gameoflife.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"


int isLiveOrDead(Image *image, int row, int col)
{
	if (row >= image->rows) {
		row -= image->rows;
	} else if (row < 0) {
		row += image->rows;
	}
	if (col >= image->cols) {
		col -= image->cols;
	} else if (col < 0) {
		col += image->cols;
	}

	if (image->image[row][col].R == 255) {
		return 1;
	} else {
		return 0;
	}
}

int calculateLiveNeighbors(Image *image, int row, int col) {
	int sum = 0;
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (i == 0 && j == 0) {
				continue;
			} else {
				sum += isLiveOrDead(image, row + i, col +j);
			}
		}
	}
	return sum;
}

int stateInNextGeneration(Image *image, int row, int col, uint32_t rule) {
	int liveCnt = calculateLiveNeighbors(image, row, col);

	if (image->image[row][col].R == 255) {
		if (rule & (1 << (liveCnt + 9))) {
			return 1;
		}
	} else {
		if (rule & (1 << liveCnt)) {
			return 1;
		}
	}
	return 0;
}

//Determines what color the cell at the given row/col should be. This function allocates space for a new Color.
//Note that you will need to read the eight neighbors of the cell in question.
//The grid "wraps", so we treat the top row as adjacent to the bottom row
//and the left column as adjacent to the right column.
Color *evaluateOneCell(Image *image, int row, int col, uint32_t rule)
{
	//YOUR CODE HERE
	Color* curr = (Color*)malloc(sizeof(Color));
	if (curr == NULL) {
		printf("error malloc Color\n");
		exit(-1);
	}

	if (stateInNextGeneration(image, row, col, rule) == 1) {
		curr->R = 255;
		curr->G = 255;
		curr->B = 255;
	} else {
		curr->R = 0;
		curr->G = 0;
		curr->B = 0;
	}

	return curr;
}

//The main body of Life; given an image and a rule, computes one iteration of the Game of Life.
//You should be able to copy most of this from steganography.c
Image *life(Image *image, uint32_t rule)
{
	//YOUR CODE HERE
	Image *next_image = (Image*)malloc(sizeof(Image));
	if (!next_image) {
		// Check for malloc failure
		exit(-1);
	}
	next_image->rows = image->rows;
	next_image->cols = image->cols;
	next_image->image = (Color **) malloc(sizeof(Color *) * next_image->rows * next_image->cols);
	if (!next_image->image) {
		// Check for malloc failure
		free(next_image);
		exit(-1);
	}
	for (int i = 0; i < next_image->rows * next_image->cols; i++) {
		next_image->image[i] = (Color *) malloc(sizeof(Color));
		if (!next_image->image[i]) {
			// Check for malloc failure
			for (int k = 0; k < i; k++) {
				free(next_image->image[k]);
			}
			free(next_image->image);
			free(next_image);
			exit(-1);
		}

		Color *tmp = evaluateOneCell(image, i / next_image->cols, i % next_image->cols, rule);
		next_image->image[i] = tmp;
		free(tmp);
	}
	return next_image;
}

/*
Loads a .ppm from a file, computes the next iteration of the game of life, then prints to stdout the new image.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a .ppm.
argv[2] should contain a hexadecimal number (such as 0x1808). Note that this will be a string.
You may find the function strtol useful for this conversion.
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!

You may find it useful to copy the code from steganography.c, to start.
*/
int main(int argc, char **argv) {
	//YOUR CODE HERE
	if (argc != 3) {
		// Check for correct number of arguments
		printf("Usage: %s <filename>\n", argv[0]);
		exit(-1);
	}
	Image *image = readData(argv[1]);
	if (!image) {
		// Check for readData failure
		exit(-1);
	}
	Image *next_image = life(image, (uint32_t)strtol(argv[2], NULL, 16));
	if (!next_image) {
		// Check for steganography failure
		freeImage(image);
		exit(-1);
	}
	writeData(next_image);
	freeImage(image);
	freeImage(next_image);
}
