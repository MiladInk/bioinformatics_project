#!/bin/bash
rm ../Data/Trees/UPGMA.trees
rm ../Data/Trees/NJ.trees
for filename in ../Data/Dists/*.csv; do
     name="$(basename "$filename")"
     name=${name%.*}
     chmod +x tree_drawer.py
     path1="../Data/Trees/"$name"_UPGMA.png"
     { ./UPGMA < "$filename";echo $path1; } | ./tree_drawer.py 
     pathm="../Data/Trees/"$name"_NJ.png"
     { ./Neighbour_Joining < "$filename";echo $pathm; } | ./tree_drawer.py   
    if [[ "$name" != "genome" && "$name" != "all_and_marburg" ]]; then
     ./UPGMA < "$filename" >> ../Data/Trees/UPGMA.trees;
     ./Neighbour_Joining < "$filename" >> ../Data/Trees/NJ.trees;
     fi
done