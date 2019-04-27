#! /bin/sh

g++ -O2 -o dunnIndex_seq dunnIndex_seq.cpp
g++ -O2 -fopenmp -o dunnIndex_par dunnIndex_par.cpp
g++ -O2 -o DBindex_seq DBindex_seq.cpp
g++ -O2 -fopenmp -o DBindex_par DBindex_par.cpp

############ Dunn on 2d Data ################## 

echo "Sequential Dunn Index on 2d with 2 clusters: "
./dunnIndex_seq 100000 2 2 2testClusters_2D_100kpoints.txt


echo "\nSequential Dunn Index on 2d with 3 clusters: "
./dunnIndex_seq 100000 3 2 3testClusters_2D_100kpoints.txt

echo "\nParallel Dunn Index on 2d with 2 clusters and 2 threads: "
./dunnIndex_par 100000 2 2 2 2testClusters_2D_100kpoints.txt

echo "\nParallel Dunn Index on 2d with 3 clusters and 2 threads: "
./dunnIndex_par 100000 3 2 2 3testClusters_2D_100kpoints.txt


echo "\nParrallel Dunn Index on 2d with 2 clusters and 4 threads: "
./dunnIndex_par 100000 2 2 4 2testClusters_2D_100kpoints.txt


echo "\nParrallel Dunn Index on 2d with 3 clusters and 4 threads: "
./dunnIndex_par 100000 3 2 4 3testClusters_2D_100kpoints.txt

echo "\nParallel Dunn Index on 2d with 2 clusters and 8 threads: "
./dunnIndex_par 100000 2 2 8 2testClusters_2D_100kpoints.txt


echo "\nParrallel Dunn Index on 2d with 3 clusters and 8 threads: "
./dunnIndex_par 100000 3 2 8 3testClusters_2D_100kpoints.txt

############ Dunn on 10d Data ##################

echo "\nSequential Dunn Index on 10d with 2 clusters: "
./dunnIndex_seq 100000 2 10 2testClusters_10D_100kpoints.txt


echo "\nSequential Dunn Index on 10d with 3 clusters: "
./dunnIndex_seq 100000 3 10 3testClusters_10D_100kpoints.txt

echo "\nParallel Dunn Index on 10d with 2 clusters and 2 threads: "
./dunnIndex_par 100000 2 10 2 2testClusters_10D_100kpoints.txt

echo "\nParallel Dunn Index on 10d with 3 clusters and 2 threads: "
./dunnIndex_par 100000 3 10 2 3testClusters_10D_100kpoints.txt

echo "\nParrallel Dunn Index on 10d with 2 clusters and 4 threads: "
./dunnIndex_par 100000 2 10 4 2testClusters_10D_100kpoints.txt


echo "\nParrallel Dunn Index on 10d with 3 clusters and 4 threads: "
./dunnIndex_par 100000 3 10 4 3testClusters_10D_100kpoints.txt

echo "\nParallel Dunn Index on 10d with 2 clusters and 8 threads: "
./dunnIndex_par 100000 2 10 8 2testClusters_10D_100kpoints.txt

echo "\nParrallel Dunn Index on 10d with 3 clusters and 8 threads: "
./dunnIndex_par 100000 3 10 8 3testClusters_10D_100kpoints.txt

############### DB Index on 2d Data #################

echo "\nSequential DB Index on 2d with 2 clusters: "
./DBindex_seq 100000 2 2 2testClusters_2D_100kpoints.txt

echo "\nSequential DB Index on 2d with 3 clusters: "
./DBindex_seq 100000 3 2 2testClusters_2D_100kpoints.txt

echo "\nParallel DB Index on 2d with 2 clusters and 2 threads: "
./DBindex_par 100000 2 2 2 2testClusters_2D_100kpoints.txt

echo "\nParrallel DB Index on 2d with 3 clusters and 2 threads: "
./DBindex_par 100000 3 2 2 2testClusters_2D_100kpoints.txt

echo "\nParallel DB Index on 2d with 2 clusters and 4 threads: "
./DBindex_par 100000 2 2 4 2testClusters_2D_100kpoints.txt

echo "\nParrallel DB Index on 2d with 3 clusters and 4 threads: "
./DBindex_par 100000 3 2 4 2testClusters_2D_100kpoints.txt

echo "\nParallel DB Index on 2d with 2 clusters and 8 threads: "
./DBindex_par 100000 2 2 8 2testClusters_2D_100kpoints.txt

echo "\nParrallel DB Index on 2d with 3 clusters and 8 threads: "
./DBindex_par 100000 3 2 8 2testClusters_2D_100kpoints.txt

############### DB Index on 10d Datas ##############

echo "\nSequential DB Index on 10d with 2 clusters: "
./DBindex_seq 100000 2 10 2testClusters_10D_100kpoints.txt

echo "\nSequential DB Index on 10d with 3 clusters: "
./DBindex_seq 100000 3 10 2testClusters_10D_100kpoints.txt

echo "\nParallel DB Index on 10d with 2 clusters and 2 threads: "
./DBindex_par 100000 2 10 2 2testClusters_10D_100kpoints.txt

echo "\nParrallel DB Index on 10d with 3 clusters and 2 threads: "
./DBindex_par 100000 3 10 2 2testClusters_10D_100kpoints.txt

echo "\nParallel DB Index on 10d with 2 clusters and 4 threads: "
./DBindex_par 100000 2 10 4 2testClusters_10D_100kpoints.txt

echo "\nParrallel DB Index on 10d with 3 clusters and 4 threads: "
./DBindex_par 100000 3 10 4 2testClusters_10D_100kpoints.txt

echo "\nParallel DB Index on 10d with 2 clusters and 8 threads: "
./DBindex_par 100000 2 10 8 2testClusters_10D_100kpoints.txt

echo "\nParallel DB Index on 10d with 3 clusters and 8 threads: "
./DBindex_par 100000 3 10 8 2testClusters_10D_100kpoints.txt
