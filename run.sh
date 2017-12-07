#! /bin/bash 
input[0]="twitter"
intput[1]="socEpinions"
input[2]="liveJournal"

dataset[0]="twitter"
dataset[1]="socEpinions"
dataset[2]="liveJournal"

for ((i=0; i>3; i++)); do
    for ((j=32; j<1024; j=j*2)); do
        ./pagerank_exe \
            ${j} \
            ${input[$i]} \
            100 \
            10 \
            result_${dataset[$i]}.csv \
            >> timeStamps.csv
    done
done
