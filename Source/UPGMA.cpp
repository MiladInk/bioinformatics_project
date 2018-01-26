//In the name of God
//written by:Milad Aghajohari
//date:8/9/1396
#include <iostream>
#include <algorithm>
#include <string>
#include <set>
#define mp make_pair
#define fi first
#define se second
using namespace std;

const int N_MAX = 1000;
const int DIST_MIN = -int(1e9) - 7; //your maximum distance should be lower than this
const int N_MAX_PROG = 2 * N_MAX;   /* maximum number of vertices this code will use
                           running neighbour joining algorithm*/
float sim[N_MAX_PROG][N_MAX_PROG];  // distance matrix
string name[N_MAX_PROG];            // names for the vertices
int n;                              // number of leaves
int num[N_MAX_PROG];
int avail_node = 0; // the number for next node
set<int> vertices;  // present vertices in the tree

int main()
{
    cin >> n;       // get the number of leaves
    avail_node = n; //next available node number is
    //get the names of our leaves
    for (int i = 0; i < n; i++)
        cin >> name[i], num[i] = 1, vertices.insert(i);
    //get the similarity matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> sim[i][j];

    //loop until the number of vertices remained is just one
    while (vertices.size() > 1)
    {
        int nver = vertices.size();
        //---find the maximum similarity
        pair<int, int> max_v = mp(-1, -1);
        float max_sim = DIST_MIN;
        for (auto v1 : vertices)
            for (auto v2 : vertices)
                if (v1 != v2 && sim[v1][v2] > max_sim)
                {
                    max_v = mp(v1, v2), max_sim = sim[v1][v2];
                }
        //---add the new vertex
        vertices.erase(max_v.fi);
        vertices.erase(max_v.se);
        int new_node = avail_node;
        if (name[max_v.fi] < name[max_v.se])
            name[new_node] = "(" + name[max_v.fi] + "," + name[max_v.se] + ")";
        else
            name[new_node] = "(" + name[max_v.se] + "," + name[max_v.fi] + ")";
        num[new_node] = num[max_v.fi] + num[max_v.se];
        vertices.insert(new_node);
        avail_node++;

        //cout << int(max_sim) << " " << name[new_node] << endl;
        for (auto v1 : vertices)
            sim[new_node][v1] = sim[v1][new_node] = (sim[max_v.fi][v1] * num[max_v.fi] + sim[max_v.se][v1] * num[max_v.se]) / (1.0 * (num[max_v.fi] + num[max_v.se]));
    }
    cout << name[avail_node - 1] << endl;
    /*printing section*/
    set<int> leaves;
}
