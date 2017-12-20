# Multithreading Pagrank Implementation

This project provides implementation of PageRank algorithm on multithreading
version on shared memory. This implementation evaluates and run on cluster
sith0. This implementation based on use of Pthread library.

This project includes directories:
    * src : There are all the scr code
    * datasets : There are src code to generate a randome graph dataset for the
      experiments.
    * metrics : There are all the metrics from the experiments.
    * presentation : The presentation slides.


# How to Make

## Generate Graphs
    make generateGraphs

## Multithreadin Pagerank Put Threads In Cores Fill Soccet By Soccet
    make pagerank

## Multithreading Pagerank Put Thread in Core In Different Soccets
    make sockArr_pagerank

## Remove All
    make removeAll


#Run The Experiments
    make runAll


