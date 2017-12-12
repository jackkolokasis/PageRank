#! /bin/bash 
dataset[0]="datasets/graph_1000_10000.txt"
dataset[1]="datasets/graph_10000_1000000.txt"
dataset[2]="dataset/graph_10000_10000000.txt"

for ((j=2; j<64; j=j*2)); do
    ./pagerank_exe \
    ${j} \
    ${dataset[0]} \
    1000 \
    10 \
    result_graph_1000_10000.csv \
    >> timeStamps.csv
done

for ((j=2; j<64; j=j*2)); do
    ./pagerank_exe \
    ${j} \
    ${dataset[1]} \
    10000 \
    10 \
    result_graph_10000_1000000.csv \
    >> timeStamps.csv
done

for ((j=2; j<64; j=j*2)); do
    ./pagerank_exe \
    ${j} \
    ${dataset[2]} \
    10000 \
    10 \
    result_graph_10000_10000000.csv \
    >> timeStamps.csv
done

