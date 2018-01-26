#include <iostream>
#include <string>
#include <string.h>
#include <cmath>
#include <algorithm>
#define mp make_pair
#define fi first
#define se second
using namespace std;
string genome; //here we will store the refrence genome
string gene;   //here we will store the gene we are going to find in the refrence genome
bool verbose = false;
const int MAX_GENOME_LENGTH = 30000 + 10;
const int MAX_GENE_LENGTH = 10000 + 10;
const int GAP_COST = -1;
const int DIF_VAL = -1;
const int EQ_VAL = 1;
/*
    score[i][j] is the best score of mapping 
    a part starting with arbitrary genome[j]...genome[i-1]
    with the part in gene[1]...gene[j-1]
*/
int score[MAX_GENOME_LENGTH][MAX_GENE_LENGTH];
pair<int, int> history[MAX_GENOME_LENGTH][MAX_GENE_LENGTH];

/*
    this function is used tp access dp cells because we wanted to 
    handle i<0 && j<0 accesses more comfortable and not hard code it
    in every access
*/
int get_dp(int i, int j)
{
    return score[i][j];
}

pair<int, int> get_mapped_range_in_genome()
{
    int max_i = 0;
    /*
        find the end of the mapped region so
        we can drop a part from the end of the genome
        we handled dropping a part from the first of genome in code before
        but now we handle dropping a part from the end of genome
    */
    for (int i = 0; i < genome.length() + 1; i++)
        if (score[i][gene.length()] > score[max_i][gene.length()])
            max_i = i;
    /*      but what is the first of the mapped region?
        we will use history part of our program to remebmer this.
        It sufficies to loop back to when someone get updated from itself
    */
    pair<int, int> var = mp(max_i, gene.length());
    // cout <<"history began" << endl;
    while (var.se != 0)
    {
        /*
        log the history for debug
        */
        // cout << var.fi <<" "<<var.se << endl;

        var = history[var.fi][var.se];
    }
    // cout << var.fi <<" "<<var.se << endl;
    // cout << "history ended" << endl;
    return mp(var.fi + 1, max_i);
}

int main(int argc, const char **argv)
{
    /*input format: genome, gene*/
    cin >> genome >> gene;
    /*check if the limits are not reached*/
    if (genome.length() > MAX_GENOME_LENGTH)
        cout << "MAX_GENOME_LENGTH is exceeded." << endl;
    if (gene.length() > MAX_GENE_LENGTH)
        cout << "MAX_GENE_LENGTH is exceeded." << endl;
    /*should be verbose?*/
    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-verbose") == 0)
        {
            verbose = true;
        }
    }

    if (verbose == true)
    {
        cout << "refrence genome is : " << genome << endl;
        cout << "gene : " << gene << endl;
    }

    /* initialize some variables, it seems it sufficies to fill
       just the first row and first column*/
    score[0][0] = 0;
    history[0][0] = mp(0, 0);
    for (int i = 1; i < genome.length() + 1; i++)
    {
        score[i][0] = 0;
        history[i][0] = mp(i, 0);
    }
    for (int i = 1; i < gene.length() + 1; i++)
    {
        score[0][i] = GAP_COST * i;
        history[0][i] = mp(0, i - 1);
    }
    /*we are going to fill dynamic programming array here*/
    for (int i = 1; i < genome.length() + 1; i++)
    {
        for (int j = 1; j < gene.length() + 1; j++)
        {
            /*
                here we check making GAPS, just making a gap and
                then continue, this can be good in many cases but we
                will take care of not penalty the dp for dropping the first part of 
                genome at the end of this loop 
            */
            score[i][j] = get_dp(i - 1, j) + GAP_COST;
            history[i][j] = mp(i - 1, j);
            if (score[i][j] < get_dp(i, j - 1) + GAP_COST)
            {
                score[i][j] = get_dp(i, j - 1) + GAP_COST;
                history[i][j] = mp(i, j - 1);
            }
            /*
            if we are going to map these two character together
            if genome[i-1] == gene[j-1] so this can get EQ_VAL and then dp[i-1][j-1]
            if genome[i-1]!= gene[j-1] so this can get a DIF_VAL penalty and then dp[i-1][j-1]
            maybe you ask a GAP is better but it depends on DIF_VAL and EQ_VAL for example
            if DIF_VAL is or small it seems better to map the unmatching characters instead of 
            just making two gaps
            */
            if (genome[i - 1] == gene[j - 1])
            {
                if (score[i][j] < get_dp(i - 1, j - 1) + EQ_VAL)
                {
                    score[i][j] = get_dp(i - 1, j - 1) + EQ_VAL;
                    history[i][j] = mp(i - 1, j - 1);
                }
            }
            else
            {
                if (score[i][j] < get_dp(i - 1, j - 1) + DIF_VAL)
                {
                    score[i][j] = get_dp(i - 1, j - 1) + DIF_VAL;
                    history[i][j] = mp(i - 1, j - 1);
                }
            }
        }
    }

    /*
        we came a long way, but what is the result? we should
        give which range of the genome we matched the gene to
        that's a crucial part and if the answer is wrong
        All we did was trash:(
            the other side of the coin is if the answer to this part is true,
            we just reached our ultimate goal of finding a part of genome
            similiar to given gene
    */
    pair<int, int> ans = get_mapped_range_in_genome();
    // cout <<"Index "<< ans.fi << " to " << ans.se <<
    // " of the genome with score " << score[ans.se][gene.length()]<< endl;
    // cout << "The found string is :" << endl;
    cout << genome.substr(ans.fi - 1, ans.se - ans.fi + 1) << endl;
}