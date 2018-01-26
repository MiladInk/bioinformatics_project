#include <iostream>
#include <string>
#include <string.h>
#include <unistd.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sys/wait.h>
#include <signal.h>
#define MAX_GENE_LENGTH 20000 + 10
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
vector<pair<string, string>> marburg_genes; // here we store the murburg's genes first:gene_name second gene_string
vector<pair<string, string>> ebola_genomes;

void signal_callback_handler(int signum)
{
}

int main()
{
    signal(SIGCHLD, signal_callback_handler);
    ifstream marburg;
    marburg.open("../Data/Marburg_Genes.fasta");
    string inp;
    while (marburg >> inp)
    {
        if (inp[0] == '>')
        {
            inp = inp.substr(1);
            marburg_genes.pb(mp(inp, ""));
            continue;
        }
        marburg_genes.back().se = marburg_genes.back().se + inp;
    }
    //printing the maruburg_genes
    for (auto marburg_gene : marburg_genes)
    {
        //cout << marburg_gene.fi << " : " << marburg_gene.se << endl;
        for (int i = 0; i < strlen(marburg_gene.se.c_str()); i++)
            if (marburg_gene.se[i] == '\n')
                cout << i << " : " << strlen(marburg_gene.se.c_str()) << endl;
    }
    /* now we have read the marburg's genes. we are going to read the genome of other types
    making a file for their genes*/
    ifstream fin_genome;
    //looping over multiple ebola's type genes
    for (auto name : names)
    {
        ebola_genomes.pb(mp(name, ""));
        string file_name = "../Data/Genomes/" + name + "_genome.fasta";
        fin_genome.open(file_name);
        getline(fin_genome, inp); //here is the name of the type pf the eboal virus, going to trash
        while (fin_genome >> inp)
        {
            ebola_genomes.back().se = ebola_genomes.back().se + inp;
        }
        fin_genome.close();
    }
    //printing the genomes
    for (auto ebola_genome : ebola_genomes)
    {
        //cout << ebola_genome.fi << " : " << ebola_genome.se << endl;
        for (int i = 0; i < strlen(ebola_genome.se.c_str()); i++)
            if (ebola_genome.se.c_str()[i] == '\n')
                cout << i << " : " << strlen(ebola_genome.se.c_str()) << endl;
    }
    int pipes[2][2];
    char *semi_local[] = {"semi_local_align", 0};
    int count = 0;
    for (auto ebola_genome : ebola_genomes)
    {
        ofstream fout;
        string out_name = "../Data/Genes/" + ebola_genome.fi + "_genes.fasta";
        fout.open(out_name.c_str());
        for (auto marburg_gene : marburg_genes)
        {
            cout << count++ << endl;
            pipe(pipes[0]);
            pipe(pipes[1]);
            int cpid = 0;
            if ((cpid = fork()) == 0)
            {
                int child_pid = getpid();
                dup2(pipes[0][0], STDIN_FILENO);
                dup2(pipes[1][1], STDOUT_FILENO);
                close(pipes[0][0]);
                close(pipes[0][1]);
                close(pipes[1][0]);
                close(pipes[1][1]);
                execv(semi_local[0], semi_local);
            }
            else
            {
                close(pipes[0][0]);
                close(pipes[1][1]);
                write(pipes[0][1], (void *)ebola_genome.se.c_str(), ebola_genome.se.length());
                write(pipes[0][1], "\n", 1);
                write(pipes[0][1], (void *)marburg_gene.se.c_str(), marburg_gene.se.length());
                write(pipes[0][1], "\n", 1);
                waitpid(cpid, 0, 0);
                char buffer[MAX_GENE_LENGTH];
                memset(buffer, 0, MAX_GENE_LENGTH);
                read(pipes[1][0], buffer, MAX_GENE_LENGTH);
                fout << ">" << marburg_gene.fi << endl;
                fout << buffer << endl;
            }
        }
        fout.close();
    }
    cout << "ended" << endl;
    return 0;
}
