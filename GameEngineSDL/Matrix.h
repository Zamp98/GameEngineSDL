#pragma once
#include <stdlib.h>
#include <stdio.h>

#define DIMENSION 4

class Matrix {
public:
	float values[DIMENSION][DIMENSION];
	float ** copy(float** a, int l, int k) {
		int i;
		for (i = 0; i < l; i++) {
			int j;
			for (j = 0; j < k; j++)
				a[i][j] = values[i][j];
		}
		return a;
	}
	void init() {
		int i, j;
		for (i = 0; i < DIMENSION; i++)
			for (j = 0; j < DIMENSION; j++)
				values[i][j] = 0;
	}
};
Matrix scaleMatrix(float a[DIMENSION][DIMENSION], float value);
Matrix addMatrix(float a[DIMENSION][DIMENSION], float b[DIMENSION][DIMENSION]);
Matrix multiplyMatrix(float a[DIMENSION][DIMENSION], float b[DIMENSION][DIMENSION]);