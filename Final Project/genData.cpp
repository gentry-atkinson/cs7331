#include <fstream>
#include <iostream>
#include <random>

using namespace std;

int main(int argc, char** argv){
    if (argc != 4){
        cerr << "Syntax is genData num_clusters num_points num_dimensions" << endl;
    }

    const int num_clusters = atoi(argv[1]);
    const int num_points = atoi(argv[2]);
    const int dimensions = atoi(argv[3]);


    return 0;
}
