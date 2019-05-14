/***********************************
*Author: Gentry Atkinson
*Class: CS7331, Spring 2019
*Assignment: Homework 1
*Due: 15 May 2019
*Description: this program will apply openMP to a large, randomized matrix
* multiplication.
***********************************/

#include<iostream>
#include <omp.h>
#include <chrono>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main(int argc, char** argv){
    const int matrixSize = atoi(argv[1]);
    cout << "Building matrixes with size: " << matrixSize << endl;

    int a[matrixSize][matrixSize];
    int b[matrixSize][matrixSize];
    int c[matrixSize][matrixSize];
    int *p = &c[0][0];

    int i,j,k, sum;

    srand(time(NULL));

    for (i = 0; i < matrixSize; ++i){
        for (int j = 0; j < matrixSize; ++j){
            a[i][j] = rand() % 10;
            b[i][j] = rand() % 10;
        }
    }

    #pragma parallel for num_threads(1) private(i, j)
    for (k = 0; k < matrixSize; ++k){
        #pragma parallel for
        for (i = 0; i < matrixSize; ++i){
            sum = 0;
            #pragma parallel for reduction (+:sum)
            for (j = 0; j < matrixSize; ++j){
                sum += a[i][j] * b[j][i];
            }
            cout << sum << endl;
            c[k][i] = sum;
        }
    }
}
