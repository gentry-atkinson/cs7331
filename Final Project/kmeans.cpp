#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cfloat>

using namespace std;

struct point{
	int cluster;
	float* values;
};

float euDis(point, point, int);

int main(int argc, char** argv){
	if (argc != 4) {
		cerr << "Command format is \"kmeans k input_file dimensions\"" << endl;
		return 1;
	}

	int listSize = 10;
	point* pointList = new point[listSize];
	int numberOfPoints = 0;
	const int k = atoi(argv[1]);
	string inFileName = argv[2];
	const int dimensions = atoi(argv[3]);
	ifstream inFile(inFileName);
	point centroidList[k];
	bool done;

	//Read in the input file
	while (!inFile.eof()){
		//max list size has been reached. Expand
		if (numberOfPoints >= listSize){
			listSize *= 2;
			point* newList = new point[listSize];
			for (int i = 0; i < numberOfPoints; i++){
                newList[i].values = new float[dimensions];
				for(int j = 0; j < dimensions; ++j){
                    newList[i].values[j] = pointList[i].values[j];
                }
				newList[i].cluster = pointList[i].cluster;
			}
			pointList = newList;
		}

		pointList[numberOfPoints].values = new float[dimensions];
		for(int i = 0; i < dimensions; ++i){
            inFile >> pointList[numberOfPoints].values[i];
		}
		pointList[numberOfPoints].cluster = -1;
		numberOfPoints++;
	}

	//Initialize centroids
	srand(time(NULL));
	for (int c = 0; c < k; c++){
		int randomPoint = rand() % numberOfPoints;
		centroidList[c].values = new float[dimensions];
		for (int i = 0; i < dimensions; ++i){
            centroidList[c].values[i] = pointList[randomPoint].values[i];
		}
	}

	//Loop until the centroids do not shift
	do {
		done = true;
		//assign points to centroids
		for (int p = 0; p < numberOfPoints; p++){
			float thisDist = 0;
			float lastDist = FLT_MAX;
			for (int c = 0; c < k; c++){
				thisDist = euDis(pointList[p], centroidList[c], dimensions);
				if (thisDist < lastDist){
					pointList[p].cluster = c;
					lastDist = thisDist;
				}
			}

		}

		//adjust centroids
		//float xSum[k];
		//float ySum[k];
		float sums[k][dimensions];
		float totalPoints[k];
		for (int c = 0; c < k; c++){ //initialize all sums to 0
			for(int i = 0; i < dimensions; ++i){
                sums[c][i] = 0;
			}
			totalPoints[c] = 0;
		}
		for (int p = 0; p < numberOfPoints; p++){  //sum across all dimensions for all points
			for (int i = 0; i < dimensions; ++i){
                sums[pointList[p].cluster][i] += pointList[p].values[i];
			}
			totalPoints[pointList[p].cluster] += 1;
		}

		for (int c = 0; c < k; c++){
            float newVals[dimensions];
			for (int i = 0; i < dimensions; ++i){
                newVals[i] = (totalPoints[c] > 0)?(sums[c][i] / totalPoints[c]):0;
			}

			for (int i = 0; i < dimensions; ++i){
                if (newVals[i] != centroidList[c].values[i] && newVals[i] != 0){
                    centroidList[c].values[i] = newVals[i];
                    done = false;
                }
			}
		}
	}while(!done);

	//output the result
	for (int p = 0; p < numberOfPoints; p++){
		for (int i = 0; i < dimensions; ++i){
            cout << pointList[p].values[i] << " ";
		}
		cout << pointList[p].cluster + 1 << endl;
	}

	return 0;
}


float euDis(point p, point c, int d){
	float dist = 0;
	for (int i = 0; i < d; ++i){
        dist += ((p.values[i] - c.values[i]) * (p.values[i] - c.values[i]));
	}
	dist = sqrt(dist);
	return dist;
}
