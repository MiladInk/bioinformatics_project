#include <iostream>
#include <string>
#include <string.h>
#include <unistd.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sys/wait.h>
#define MAX_GENE_LENGTH 20000 + 10
#define fi first
#define se second
#define pb push_back
#define mp make_pair
using namespace std;
/*array of the names of types of ebual virus,
  so we can read the names of viruses and then after that 
  makes the difference matrix
*/
string names[5] = {"Reston", "Sudan", "TaiForest", "Zaire", "Bundibugyo"};
struct ebola_sarde
{
    string name_sarde;
    vector<pair<string, string>> genes;
};
vector<struct ebola_sarde> ebolaes;
int main()
{
    ifstream fin_genes;
    for (auto name : names)
    {
        struct ebola_sarde ebola_sarde;
        ebola_sarde.name_sarde = name;
        string file_name = "../Data/Genes/" + name + "_genes.fasta";
        fin_genes.open(file_name);
        string inp;
        while (fin_genes >> inp)
        {
            if (inp[0] == '>')
            {
                inp = inp.substr(1);
                ebola_sarde.genes.pb(mp(inp, ""));
                continue;
            }
            ebola_sarde.genes.back().se = ebola_sarde.genes.back().se + inp;
        }
        fin_genes.close();
        ebolaes.pb(ebola_sarde);
    }

    // for (auto ebola : ebolaes)
    // {
    //     cout << "name is " << ebola.name_sarde << endl;
    //     cout << "I have " << ebola.genes.size() << " genes.\n";
    //     for (auto gene : ebola.genes)
    //     {
    //         cout << gene.se.length() << " ";
    //     }
    //     cout << endl;
    // }
    /*
        we are going to make the distance matrix for the 7 genes now
    */
    int dist[7][5][5];
    int pipes[2][2];
    char *global_align[] = {"global_align", 0};
    for (int i = 0; i < 7; i++)
    {
        for (int i_1 = 0; i_1 < 5; i_1++)
            for (int i_2 = 0; i_2 <= i_1; i_2++)
            {
                string s1 = ebolaes[i_1].genes[i].se;
                string s2 = ebolaes[i_2].genes[i].se;
                //cout << s1.substr(0, 10) << " .vs " << s2.substr(0, 10) << endl;
                pipe(pipes[0]);
                pipe(pipes[1]);
                int cpid = 0;
                if (!(cpid = fork()))
                {
                    dup2(pipes[0][0], STDIN_FILENO);
                    dup2(pipes[1][1], STDOUT_FILENO);
                    close(pipes[0][0]);
                    close(pipes[0][1]);
                    close(pipes[1][0]);
                    close(pipes[1][1]);
                    execv(global_align[0], global_align);
                    return 0;
                }
                else
                {
                    close(pipes[0][0]);
                    close(pipes[1][1]);
                    write(pipes[0][1], (void *)s1.c_str(), s1.length());
                    write(pipes[0][1], "\n", 1);
                    write(pipes[0][1], (void *)s2.c_str(), s2.length());
                    write(pipes[0][1], "\n", 1);
                    wait(NULL);
                    char buffer[MAX_GENE_LENGTH];
                    memset(buffer, 0, MAX_GENE_LENGTH);
                    read(pipes[1][0], buffer, 10);
                    int temp;
                    sscanf(buffer, "%d", &temp);
                    dist[i][i_1][i_2] = dist[i][i_2][i_1] = temp;
                }
            }
    }

    for (int i = 0; i < 7; i++)
    {
        ofstream fout;
        string file_name = "../Data/Dists/" + ebolaes[0].genes[i].fi + ".csv";
        fout.open(file_name.c_str());
        fout << 5 << endl;
        for (int j = 0; j < 5; j++)
            fout << ebolaes[j].name_sarde << endl;
        for (int i_1 = 0; i_1 < 5; i_1++)
        {
            for (int i_2 = 0; i_2 < 5; i_2++)
            {
                fout << dist[i][i_1][i_2] << " ";
                //cout << dist[i][i_1][i_2] << endl;
            }
            fout << endl;
        }
    }
}