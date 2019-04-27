#include <fstream>
#include <iostream>
#include <random>
#include <stdlib.h>
#include <time.h>
#include <iomanip>

using namespace std;

int main(int argc, char** argv){
    if (argc != 4){
        cerr << "Syntax is genData num_centers num_points num_dimensions" << endl;
        return 1;
    }

    const int num_clusters = atoi(argv[1]);
    const int num_points = atoi(argv[2]);
    const int dimensions = atoi(argv[3]);

    default_random_engine generator;
    normal_distribution<float> distribution(0, 1);

    float scale = num_clusters * 10;
    float centers[num_clusters][dimensions];

    srand(time(NULL));

    for (int i = 0; i < num_clusters; ++i){
        for (int j = 0; j < dimensions; ++j){
            centers[i][j] = (rand() % static_cast<int>(scale));
        }
    }

    int clusterPicker;
    ofstream outFile("randomPoints.txt");

    outFile << fixed << setprecision(2);

    for (int i = 0; i < num_points-1; ++i){
        clusterPicker = (rand() % num_clusters);
        for (int j = 0; j < dimensions; ++j){
            float displacement = distribution(generator);
            outFile << centers[clusterPicker][j] +  displacement << " ";
        }
        outFile << endl;
    }

    clusterPicker = (rand() % num_clusters);
    for (int j = 0; j < dimensions; ++j){
        float displacement = distribution(generator);
        outFile << centers[clusterPicker][j] +  displacement << " ";
    }

    return 0;
}
