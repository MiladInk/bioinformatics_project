#include<iostream>
#include<string>
#include<string.h>
#include <unistd.h>
#include<fstream>
#include<vector>
#include<algorithm>
#define fi first
#define se second
#define pb push_back
#define mp make_pair
using namespace std;
/*array of the names of types of ebual virus,
  we are going to align the genes of marburg virus to the below genomes
  so we can find out the genes in the different type of viruses. 
*/
string names[5] = {"Reston", "Sudan", "TaiForest", "Zaire", "Bundibugyo"};
vector<pair<string, string> > marburg_genes;// here we store the murburg's genes first:gene_name second gene_string
int main(){
    ifstream marburg;
    marburg.open("../Data/Marburg_Genes.fasta");
    string inp;
    while(marburg >> inp){
        if(inp[0] == '>'){
            inp = inp.substr(1);
            marburg_genes.pb(mp(inp, ""));
            continue;
        }
        marburg_genes.back().se = marburg_genes.back().se + inp;
    } 
    /* now we have read the marburg's genes. we are going to read the genome of other types
    making a file for their genes*/
    ifstream fin_genome;
    //looping over multiple ebola's type genes
    for(auto name: names){
        string file_name = "../Data/" + name + "_genome.fasta";
        fin_genome.open(file_name);
        string text;
        while(fin_genome >> text) cout << text << endl;
        fin_genome.close();
    }
}