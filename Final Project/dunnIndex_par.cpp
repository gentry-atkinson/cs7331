#include <fstream>
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <omp.h>
#include <limits>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct point{
	int cluster;
	float* values;
};

float euDis(point, point, int);

int main(int argc, char** argv){
	if (argc != 6) {
		cerr << "Command format is \"dunnIndex num_points num_clusters dimensions num_threads filename\"" << endl;
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
	int i;
	auto start = high_resolution_clock::now();
	//calculate centers
    float sums[numClusters][dimensions];
    float totalPoints[numClusters];
    #pragma omp parallel for
	for(i = 0; i < numClusters; ++i){   //initialize everything to 0
        int j;
        for(j = 0; j < dimensions; ++j)
            sums[i][j] = 0;
        totalPoints[i] = 0;
	}
	#pragma omp parallel for
	for (i = 0; i < numPoints; ++i){    //sum across all dimensions of the point list
        int j;
        for (j = 0; j < dimensions; ++j)
            sums[points[i].cluster-1][j] += points[i].values[j];
        totalPoints[points[i].cluster-1] += 1;
	}
    #pragma omp parallel for
	for (i = 0; i < numClusters; ++i){ //divide sum by points to get centers
        centers[i].values = new float[dimensions];
        int j;
        for (j = 0; j < dimensions; ++j){
            centers[i].values[j] = (sums[i][j] / totalPoints[i]);
        }
        centers[i].cluster = i+1;
	}
	float minInterClusterDist = bound.max();
	float maxIntraClusterDist = 0;

	//calculate min inter-cluster distance
	for (i = 0; i < numClusters-1; ++i){
        int j = i+1;
        for (; j < numClusters; ++j){
            float thisDist = euDis(centers[i], centers[j], dimensions);
            if (thisDist < minInterClusterDist)
                minInterClusterDist = thisDist;
        }
	}
	//calculate max intra-cluster distance
	#pragma omp parallel for
	for (i = 0; i < numPoints-1; ++i){
        float thisDist = euDis(points[i], centers[points[i].cluster-1], dimensions);
        if (thisDist > maxIntraClusterDist){
            maxIntraClusterDist = thisDist;
        }
	}

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);

    cout << "Dunn Index: " << minInterClusterDist/maxIntraClusterDist << endl;
    cout << "Time to run: " << (duration.count())/1000.0 << " milliseconds." << endl;

	return 0;
}

float euDis(point p, point c, int d){
	float dist = 0;
	#pragma omp parallel for
	for (int i = 0; i < d; ++i){
        dist += ((p.values[i] - c.values[i]) * (p.values[i] - c.values[i]));
	}
	dist = sqrt(dist);
	return dist;
}
