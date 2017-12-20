#--------------------------------------
#
# Author : Jack Kolokasis
# email  : kolokasis@csd.uoc.gr
#
#--------------------------------------

generateGraphs:
	cd datasets && make all
	cd datasets && make generate

sockArr_pagerank:
	cd src && make NUMA+="NUMA_SOCKARR" all
	cd src && cp pagerank_exe ../

pagerank:
	cd src && make all
	cd src && cp pagerank_exe ../

runAll:
	./run.sh

removeAll:
	cd dataset && make removeAll
	cd src && make clean
	rm -rf result_graph_* timeStamps* 


