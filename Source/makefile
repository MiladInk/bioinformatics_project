all:  ../Data/Trees/*.tree Neighbour_Joining UPGMA semi_local_align gene_finder gene_distance_maker global_align ../Data/Dists/*.csv ../Data/Genes/*.fasta

../Data/Dists/*.csv: gene_distance_maker ../Data/Genes/*.fasta
	./gene_distance_maker
../Data/Genes/*.fasta: gene_finder ../Data/Genomes/*.fasta
	./gene_finder
global_align: global_align.cpp
	g++ --std=c++11 global_align.cpp -o global_align

gene_finder: gene_finder.cpp semi_local_align
	g++ --std=c++11 gene_finder.cpp -o gene_finder

gene_distance_maker: gene_distance_maker.cpp global_align
	g++ --std=c++11 gene_distance_maker.cpp -o gene_distance_maker

semi_local_align:	semi_local_align.cpp
	g++ --std=c++11 semi_local_align.cpp -o semi_local_align
UPGMA: UPGMA.cpp
	g++ --std=c++11 UPGMA.cpp -o UPGMA
Neighbour_Joining: Neighbour_Joining.cpp
	g++ --std=c++11 Neighbour_Joining.cpp -o Neighbour_Joining
../Data/Trees/*.tree: ../Data/Dists/*.csv
	chmod +x tree_making.sh
	./tree_making.sh
	

