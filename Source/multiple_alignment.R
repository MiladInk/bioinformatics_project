#!/usr/bin/Rscript
# source("https://bioconductor.org/biocLite.R")
# biocLite()
library(Biostrings)
library(readtext)
inp<-readLines(file("stdin"), n = 1)
s1<-inp
# from here I got the code : https://bioconductor.org/packages/devel/bioc/vignettes/Biostrings/inst/doc/PairwiseAlignments.pdf
submat <- matrix(-1, nrow = 26, ncol = 26, dimnames = list(letters, letters))
diag(submat) <- 0
pairwiseAlignment(pattern = s1, subject = "sah",
                    substitutionMatrix = submat,
                    gapOpening = 0, gapExtension = 1)
