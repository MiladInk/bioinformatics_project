#!/usr/bin/env python
from Bio import Phylo
from io import StringIO
import matplotlib.pyplot as plt
str = input()
pat = "salam"
try:
    pat = input()
except EOFError:
    a = 10
inp = StringIO(str)
tree = Phylo.read(inp, "newick")
Phylo.draw(tree, do_show=False)
plt.savefig(pat)
