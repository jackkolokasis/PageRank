#! /bin/bash 
dataset[0]="datasets/graph_10000_1000000.txt"
dataset[1]="datasets/graph_10000_10000000.txt"
dataset[2]="datasets/graph_100k_20m.txt" 

for ((i=0; i<5; i++)); do
	for ((j=1; j<64; j=j*2)); do
	    ./pagerank_exe \
	    ${j} \
	    ${dataset[0]} \
	    10000 \
	    10 \
	    result_graph_10000_1000000_${i}_${j}.csv \
	    >> timeStamps_${i}.csv
	done
	
	for ((j=1; j<64; j=j*2)); do
	    ./pagerank_exe \
	    ${j} \
	    ${dataset[1]} \
	    10000 \
	    10 \
	    result_graph_10000_10000000_${i}_${j}.csv \
	    >> timeStamps_${i}.csv
	done
	
	for ((j=1; j<64; j=j*2)); do
	    ./pagerank_exe \
	    ${j} \
	    ${dataset[2]} \
	    100000 \
	    10 \
	    result_graph_10000_10000000_${i}_${j}.csv \
	    >> timeStamps_${i}.csv
	done
done

