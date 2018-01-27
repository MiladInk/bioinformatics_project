#!/usr/bin/Rscript
genome_file <-file("../Data/Dists/all_and_marburg.csv")
length_file <-file("../Data/Dists/length.txt")
lambda = 1.9*10^-3
lines<-readLines(genome_file)
n <- as.numeric(lines[1])
dist_time <- NULL
genome_length <- NULL
names <- NULL
for(i in (2):(n+1)){
  names <- c(names, unlist(as.character(lines[i])))
}
for(i in (n+2):(n+n+1)){
  dist_time <- c(dist_time, unlist(strsplit(lines[i], split = " ")))
}
for(i in (n+2):(n+n+1)){
  dist_time <- c(dist_time, unlist(strsplit(lines[i], split = " ")))
} 
lines<-readLines(length_file)
genome_length <- NULL
for(i in (n+2):(n+n+1)){
  genome_length <-c(genome_length, unlist(strsplit(lines[i], split = " ")))
} 

dist_time <- as.numeric(dist_time)
dist_time <- matrix(dist_time, nrow = n, ncol = n, byrow = TRUE)
colnames(dist_time)<- names
rownames(dist_time)<- names
length <- as.numeric(genome_length)
p <- dist_time/length
times = -3/4.*log(1-4/3.*p)/lambda
library(phangorn)
colnames(times)<- names
rownames(times)<- names
upgma_tree <- upgma(times)
png("../Data/Trees/times.png")
plot(upgma_tree)
edgelabels(round(upgma_tree$edge.length),  col="black", font=0.3)
dev.off()
