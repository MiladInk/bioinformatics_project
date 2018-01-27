all:  genome_distance_maker ../Data/Trees/*.png  ../Data/Trees/*.trees Neighbour_Joining UPGMA semi_local_align gene_finder gene_distance_maker global_align ../Data/Dists/*.csv ../Data/Genes/*.fasta

../Data/Dists/*.csv: gene_distance_maker ../Data/Genes/*.fasta genome_distance_maker ../Data/Genomes/*.fasta UPGMA
	./gene_distance_maker
	./genome_distance_maker
../Data/Genes/*.fasta: gene_finder ../Data/Genomes/*.fasta
	./gene_finder
global_align: global_align.cpp
	g++ --std=c++11 global_align.cpp -o  global_align

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

../Data/Trees/*.png: ../Data/Dists/*.csv tree_drawer.py UPGMA Neighbour_Joining ./tree_making.sh
	chmod +x tree_making.sh
	./tree_making.sh
	chmod +x time_calc.R	
	./time_calc.R
	chmod +x consensus_tree.R
	./consensus_tree.R

../Data/Trees/*.trees: ../Data/Dists/*.csv tree_drawer.py UPGMA Neighbour_Joining
	chmod +x trees_making.sh
	./trees_making.sh

genome_distance_maker: genome_distance_maker.cpp
	g++ --std=c++11 genome_distance_maker.cpp -o genome_distance_maker
clean:
	rm -f ../Data/Genes/*_genes.fasta
	rm -f ../Data/Trees/*.trees
	rm -f ../Data/Trees/*.png
	rm -f ../Data/Dists/*.csv
	rm -f ../Data/Dists/length.txt
