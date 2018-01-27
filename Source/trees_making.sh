#!/bin/bash
rm -f ../Data/Trees/UPGMA.trees
rm -f ../Data/Trees/NJ.trees
for filename in ../Data/Dists/*.csv; do
     name="$(basename "$filename")"
     name=${name%.*}
     chmod +x tree_drawer.py  
    if [[ "$name" != "genome" && "$name" != "all_and_marburg" ]]; then
     ./UPGMA < "$filename" >> ../Data/Trees/UPGMA.trees;
     ./Neighbour_Joining < "$filename" >> ../Data/Trees/NJ.trees;
     fi
done