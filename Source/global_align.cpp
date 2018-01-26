#include <iostream>
#include <string>
#include <string.h>
#include <cmath>
#include <algorithm>
#define mp make_pair
#define fi first
#define se second
using namespace std;
string genome_1; //here we will store the refrence genome
string genome_2; //here we will store the gene we are going to find in the refrence genome
bool verbose = false;
const int MAX_GENOME_LENGTH = 30000 + 10;
const int INF = int(1e9);
const int GAP_COST = -1;
const int DIF_VAL = -1;
const int EQ_VAL = 0; //it is crucial to calculate edit distance
/*
    edit[i][j] is the best edit of mapping 
    genome_1[0]..genome_1[i] to genome_2[0]...genome_2[j]
*/
int edit[MAX_GENOME_LENGTH][MAX_GENOME_LENGTH];

/*
    this function is used tp access dp cells because we wanted to 
    handle i<0 && j<0 accesses more comfortable and not hard code it
    in every access
*/
int get_dp(int i, int j)
{
    if (i < 0 || j < 0)
        return -1 * INF;
    return edit[i][j];
}

int main()
{
    /*input format: genome, gene*/
    cin >> genome_1 >> genome_2;
    /*check if the limits are not reached*/
    if (genome_1.length() > MAX_GENOME_LENGTH)
        cout << "MAX_GENOME_LENGTH is exceeded." << endl;
    if (genome_2.length() > MAX_GENOME_LENGTH)
        cout << "MAX_GENE_LENGTH is exceeded." << endl;

    /* initialize some variables, it seems it sufficies to fill
       just the first row and first column*/
    edit[0][0] = 0;
    for (int i = 1; i < genome_1.length() + 1; i++)
    {
        edit[i][0] = GAP_COST * i;
    }
    for (int i = 1; i < genome_2.length() + 1; i++)
    {
        edit[0][i] = GAP_COST * i;
    }
    /*we are going to fill dynamic programming array here*/

    for (int i = 1; i < genome_1.length() + 1; i++)
    {
        for (int j = 1; j < genome_2.length() + 1; j++)
        {
            /*
                here we check making GAPS, just making a gap and
                then continue, this can be good in many cases but we
                will take care of not penalty the dp for dropping the first part of 
                genome at the end of this loop 
            */
            edit[i][j] = get_dp(i - 1, j) + GAP_COST;
            if (edit[i][j] < get_dp(i, j - 1) + GAP_COST)
            {
                edit[i][j] = get_dp(i, j - 1) + GAP_COST;
            }
            /*
            if we are going to map these two character together
            if genome[i-1] == gene[j-1] so this can get EQ_VAL and then dp[i-1][j-1]
            if genome[i-1]!= gene[j-1] so this can get a DIF_VAL penalty and then dp[i-1][j-1]
            maybe you ask a GAP is better but it depends on DIF_VAL and EQ_VAL for example
            if DIF_VAL is or small it seems better to map the unmatching characters instead of 
            just making two gaps
            */
            if (genome_1[i - 1] == genome_2[j - 1])
            {
                if (edit[i][j] < get_dp(i - 1, j - 1) + EQ_VAL)
                {
                    edit[i][j] = get_dp(i - 1, j - 1) + EQ_VAL;
                }
            }
            else
            {
                if (edit[i][j] < get_dp(i - 1, j - 1) + DIF_VAL)
                {
                    edit[i][j] = get_dp(i - 1, j - 1) + DIF_VAL;
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
    cout << edit[genome_1.length()][genome_2.length()] * -1 << endl;
}