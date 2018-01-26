#!/usr/bin/env python
from Bio import Phylo
from io import StringIO
str = input()
inp = StringIO(str)
tree = Phylo.read(inp, "newick")
Phylo.draw_ascii(tree)
