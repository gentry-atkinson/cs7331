#include <fstream>
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <limits>
#include <omp.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct point{
	int cluster;
	float* values;
};

float euDis(point, point, int);
float calcS(const point*, point, int, int);

int main(int argc, char** argv){
		if (argc != 5) {
		cerr << "Command format is \"DBIndex num_points num_clusters dimensions num_threads filename\"" << endl;
		return 1;
	}

	numeric_limits<float> bound;
	const int numPoints = atoi(argv[1]);
	const int numClusters = atoi(argv[2]);
	const int dimensions = atoi(argv[3]);
	const int num_threads = atoi(argv[4]);
	ifstream inFile(argv[5]);

	omp_set_num_threads(num_threads);

	point points[numPoints];
	point centers[numClusters];
	int temp = 0;
	while (!inFile.eof()){
        points[temp].values = new float[dimensions];
        for (int i = 0; i < dimensions; ++i){
            inFile >> points[temp].values[i];
        }
        inFile >> points[temp].cluster;
        temp++;
	}
	auto start = high_resolution_clock::now();

	//calculate centers
    float sums[numClusters][dimensions];
    float totalPoints[numClusters];
    #pragma parallel for private(j)
	for(int i = 0; i < numClusters; ++i){   //initialize everything to 0
        for(int j = 0; j < dimensions; ++j)
            sums[i][j] = 0;
        totalPoints[i] = 0;
	}
	#pragma parallel for private(j)
	for (int i = 0; i < numPoints; ++i){    //sum across all dimensions of the point list
        for (int j = 0; j < dimensions; ++j)
            sums[points[i].cluster-1][j] += points[i].values[j];
        totalPoints[points[i].cluster-1] += 1;
	}
	#pragma parallel for private(j)
	for (int i = 0; i < numClusters; ++i){ //divide sum by points to get centers
        centers[i].values = new float[dimensions];
        for (int j = 0; j < dimensions; ++j){
            centers[i].values[j] = (sums[i][j] / totalPoints[i]);
        }
        centers[i].cluster = i+1;
	}

	float D[numClusters];
	float totalD = 0;
    #pragma parallel for private(j)
	for (int i = 0; i < numClusters-1; i++){
        D[i] = 0;
        for (int j = i+1; j < numClusters; j++){
            float S = (calcS(points, centers[i], numPoints, dimensions) + calcS(points, centers[j], numPoints, dimensions)) / euDis(centers[i], centers[j], dimensions);
            if (S > D[i])
                D[i] = S;
        }
        totalD += D[i];
	}

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);

	cout << "Davies-Boudlin Index: " << totalD / numClusters << endl;
	cout << "Time to run: " << (duration.count())/1000.0 << " milliseconds." << endl;

	return 0;
}

float euDis(point p, point c, int d){
	float dist = 0;
	#pragma parallel for
	for (int i = 0; i < d; ++i){
        dist += ((p.values[i] - c.values[i]) * (p.values[i] - c.values[i]));
	}
	dist = sqrt(dist);
	return dist;
}

float calcS(const point* points, point center, int numPoints, int d){
    int numClusterPoints = 0;
    float totalDis = 0;
    #pragma parallel for
    for (int i = 0; i < numPoints; i++){
        if (points[i].cluster == center.cluster){
            totalDis += euDis(points[i], center, d);
            numClusterPoints += 1;
        }
    }
    return totalDis / numClusterPoints;
}
