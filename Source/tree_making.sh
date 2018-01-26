#!/bin/sh
rm ../Data/Trees/UPGMA.trees
rm ../Data/Trees/NJ.trees
for filename in ../Data/Dists/*.csv; do
     name="$(basename "$filename")"
     name=${name%.*}
     chmod +x tree_drawer.py
     path1="../Data/Trees/"$name"_UPGMA.png\n"
     { ./UPGMA < "$filename";echo $path1; } | ./tree_drawer.py 
     ./UPGMA < "$filename" >> ../Data/Trees/UPGMA.trees
     path="../Data/Trees/"$name"_NJ.png\n"
     { ./Neighbour_Joining < "$filename";echo $path; } | ./tree_drawer.py 
     ./Neighbour_Joining < "$filename" >> ../Data/Trees/NJ.trees
done