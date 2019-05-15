/***********************************
*Author: Gentry Atkinson
*Class: CS7331, Spring 2019
*Assignment: Homework 1
*Due: 15 May 2019
*Description: this program will apply openMP to a large, randomized matrix
* multiplication of 3 user-input sizes.
***********************************/

#include<iostream>
#include <omp.h>
#include <chrono>
#include <stdlib.h>
#include <time.h>

using namespace std;
using namespace std::chrono;

int main(int argc, char** argv){
    if (argc != 4){
      cout << "Please enter 3 matrix sizes in ascending order" << endl;
      return 0;
    }
    const int matrixSize1 = atoi(argv[1]);
    const int matrixSize2 = atoi(argv[2]);
    const int matrixSize3 = atoi(argv[3]);
    cout << "Building matrices with sizes: " << matrixSize1;
    cout << ", " << matrixSize2 << ", and " << matrixSize3 << endl;

    int a1[matrixSize1][matrixSize1];
    int b1[matrixSize1][matrixSize1];
    int c1[matrixSize1][matrixSize1];

    int a2[matrixSize2][matrixSize2];
    int b2[matrixSize2][matrixSize2];
    int c2[matrixSize2][matrixSize2];

    int a3[matrixSize3][matrixSize3];
    int b3[matrixSize3][matrixSize3];
    int c3[matrixSize3][matrixSize3];

    int i,j,k,sum;

    srand(time(NULL));

    for (i = 0; i < matrixSize1; ++i){
        for (int j = 0; j < matrixSize1; ++j){
            a1[i][j] = rand() % 10;
            b1[i][j] = rand() % 10;
        }
    }

    for (i = 0; i < matrixSize2; ++i){
        for (int j = 0; j < matrixSize2; ++j){
            a2[i][j] = rand() % 10;
            b2[i][j] = rand() % 10;
        }
    }

    for (i = 0; i < matrixSize3; ++i){
        for (int j = 0; j < matrixSize3; ++j){
            a3[i][j] = rand() % 10;
            b3[i][j] = rand() % 10;
        }
    }
    const int numThreads1 = 1;
    const int numThreads2 = (matrixSize2 / static_cast<float>(matrixSize1))*(matrixSize2 / static_cast<float>(matrixSize1));
    const int numThreads3 = (matrixSize3 / static_cast<float>(matrixSize1))*(matrixSize3 / static_cast<float>(matrixSize1));

    auto start = high_resolution_clock::now();
    omp_set_num_threads(numThreads1);
    #pragma omp parallel for private(k, j) collapse(2) reduction(+:sum)
    for (i = 0; i < matrixSize1; ++i){
      for (j = 0; j < matrixSize1; ++j){
        sum = 0;
        for(k = 0; k < matrixSize1; ++k){
          sum += a1[i][k] * b1[k][j];
        }
        c1[i][j] = sum;
      }
    }
    auto stop = high_resolution_clock::now();
  	auto duration = duration_cast<microseconds>(stop - start);
    cout << "Multiplication one ran on: " << numThreads1 << " threads" << endl;
    cout << "Time to run matrix 1: " << (duration.count())/1000.0 << " milliseconds." << endl << endl;

    start = high_resolution_clock::now();
    omp_set_num_threads(numThreads2);
    #pragma omp parallel for private(k, j) collapse(2) reduction(+:sum)
    for (i = 0; i < matrixSize2; ++i){
      for (j = 0; j < matrixSize2; ++j){
        sum = 0;
        for(k = 0; k < matrixSize2; ++k){
          sum += a2[i][k] * b2[k][j];
        }
        c2[i][j] = sum;
      }
    }
    stop = high_resolution_clock::now();
  	duration = duration_cast<microseconds>(stop - start);
    cout << "Multiplication one ran on: " << numThreads2 << " threads" << endl;
    cout << "Time to run matrix 2: " << (duration.count())/1000.0 << " milliseconds." << endl << endl;

    start = high_resolution_clock::now();
    omp_set_num_threads(numThreads3);
    #pragma omp parallel for private(k, j) collapse(2) reduction(+:sum)
    for (i = 0; i < matrixSize3; ++i){
      for (j = 0; j < matrixSize3; ++j){
        sum = 0;
        for(k = 0; k < matrixSize3; ++k){
          sum += a3[i][k] * b3[k][j];
        }
        c3[i][j] = sum;
      }
    }
    stop = high_resolution_clock::now();
  	duration = duration_cast<microseconds>(stop - start);
    cout << "Multiplication one ran on: " << numThreads3 << " threads" << endl;
    cout << "Time to run matrix 3: " << (duration.count())/1000.0 << " milliseconds." << endl << endl;

    return 0;
}
