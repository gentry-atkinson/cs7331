#! /bin/sh

echo "Sequential Dunn Index on 2d with 2 clusters: \n"
./dunnIndex_seq 100000 2 2 2testClusters_2D_100kpoints.txt


echo "Sequential Dunn Index on 2d with 3 clusters: \n"
./dunnIndex_seq 100000 3 2 3testClusters_2D_100kpoints.txt

echo "Parallel Dunn Index on 2d with 2 clusters and 2 threads: \n"
./dunnIndex_par 100000 2 2 2 2testClusters_2D_100kpoints.txt

echo "Parallel Dunn Index on 2d with 3 clusters and 2 threads: \n"
./dunnIndex_par 100000 2 2 2 3testClusters_2D_100kpoints.txt


echo "Parrallel Dunn Index on 2d with 2 clusters and 4 threads: \n"
./dunnIndex_par 100000 3 2 4 2testClusters_2D_100kpoints.txt


echo "Parrallel Dunn Index on 2d with 3 clusters and 4 threads: \n"
./dunnIndex_par 100000 3 2 4 3testClusters_2D_100kpoints.txt

echo "Parallel Dunn Index on 2d with 2 clusters and 8 threads: \n"
./dunnIndex_par 100000 2 2 8 2testClusters_2D_100kpoints.txt


echo "Parrallel Dunn Index on 2d with 3 clusters and 8 threads: \n"
./dunnIndex_par 100000 3 2 8 3testClusters_2D_100kpoints.txt


