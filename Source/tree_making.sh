#!/bin/sh
for filename in ../Data/Dists/*.csv; do
     name="$(basename "$filename")"
     name=${name%.*}
     chmod +x tree_drawer.py
     ./UPGMA < "$filename" | ./tree_drawer.py >../Data/Trees/"$name"_UPGMA.tree
     ./Neighbour_Joining < "$filename" | ./tree_drawer.py >../Data/Trees/"$name"_Neighbour_Joining.tree
done