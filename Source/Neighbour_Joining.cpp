//In the name of God
//written by:Milad Aghajohari
//date:5/9/1396
#include <iostream>
#include <algorithm>
#include <string>
#include <set>
#define mp make_pair
#define fi first
#define se second
using namespace std;
/*This code will make the pyhlogenetic tree using your distance matrix
by using neighbour joining algorithm
complexity:This code will use O(4*n^2) space and O(n^3) time complexity
limits: limit variables are written below which you can see
here are a few notes:
your matrix distance's values are suppoused to be integer in the c++ limit
for int in your computer.
your distances should be lower than DIST_MAX.
*/
const int N_MAX = 1000;
const int DIST_MAX = int(1e9) + 7; //your maximum distance should be lower than this
const int N_NEWNODES = N_MAX;
const int N_MAX_PROG = N_MAX + N_NEWNODES; /* maximum number of vertices this code will use
                           running neighbour joining algorithm*/
float dist[N_MAX_PROG][N_MAX_PROG];        // distance matrix
float dist_star[N_MAX_PROG][N_MAX_PROG];   /* distance star matrix which is used in the neighbour joining
                                      algorithm */
float total_dist[N_MAX_PROG];              /* total distances get computed here*/
string name[N_MAX_PROG];                   // names for the vertices
int n;                                     // number of leaves
int par[N_MAX_PROG];
int edge[N_MAX_PROG][N_MAX_PROG];
int avail_node = 0; // the number for next node
set<int> vertices;  // present vertices in the tree

int main()
{
    cin >> n;       // get the number of leaves
    avail_node = n; //next available node number is
    //get the names of our leaves
    for (int i = 0; i < n; i++)
        cin >> name[i];
    for (int i = 0; i < N_MAX_PROG; i++)
        par[i] = -1;

    for (int i = 0; i < n; i++)
        vertices.insert(i);
    //get the distance matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> dist[i][j];

    //loop until the number of vertices remained is just one
    while (vertices.size() > 1)
    {
        int nver = vertices.size();
        if (nver == 2)
        {
            vector<int> v;
            v.clear();
            for (auto ver : vertices)
                v.push_back(ver);
            int a = v[0], b = v[1];
            edge[a][b] = edge[b][a] = 1;
            break;
        }
        //---construct total_dist
        for (auto v1 : vertices)
        {
            total_dist[v1] = 0;
            for (auto v2 : vertices)
                total_dist[v1] += dist[v1][v2];
        }
        //---construct dist_star matrix
        for (auto v1 : vertices)
            for (auto v2 : vertices)
                dist_star[v1][v2] = (nver - 2) * dist[v1][v2] - total_dist[v1] - total_dist[v2];
        //---find the minimum distance
        int min_v1 = -1, min_v2 = -1;
        float min_dist = DIST_MAX;
        for (auto v1 : vertices)
            for (auto v2 : vertices)
                if (v1 != v2 && dist_star[v1][v2] < min_dist)
                {
                    min_v1 = v1, min_v2 = v2, min_dist = dist_star[v1][v2];
                }

        /*join min_v1 and min_v2*/
        //---add the new vertex
        vertices.erase(min_v1);
        vertices.erase(min_v2);
        int new_node = avail_node;
        vertices.insert(new_node);
        avail_node++;
        //---calculate distances of min_v1 and min_v2 with the newly emerged vertex
        dist[min_v1][new_node] = dist[new_node][min_v1] = 0.5 * dist[min_v1][min_v2] + (total_dist[min_v1] - total_dist[min_v2]) / (2 * (nver - 2));
        dist[min_v2][new_node] = dist[new_node][min_v2] = dist[min_v1][min_v2] - dist[min_v1][new_node];
        //---calculate distance of new_node with other nodes
        for (auto v1 : vertices)
            dist[new_node][v1] = dist[v1][new_node] = 0.5 * (dist[min_v1][v1] + dist[min_v2][v1] - dist[min_v1][min_v2]);
        edge[min_v1][new_node] = edge[new_node][min_v1] = 1;
        edge[min_v2][new_node] = edge[new_node][min_v2] = 1;
        // cout <<"join them : " << min_v1 << ","<<min_v2 <<"to"<<new_node<< endl;
    }

    /*printing section*/
    set<int> leaves;

    while (1)
    {
        leaves.clear();
        for (int i = 0; i < avail_node; i++)
        {
            int sum = 0;
            for (int j = 0; j < avail_node; j++)
            {
                sum += edge[i][j];
                if (edge[i][j])
                    par[i] = j;
            }
            if (sum == 1)
                leaves.insert(i);
        }
        // cout<<"leaves are:";
        // for(auto leaf:leaves)
        //   cout << "name:"<<name[leaf] <<" ";
        //   for(int i = 0; i<avail_node; i++){
        //     if(leaves.find(i) == leaves.end())
        //       continue;
        //       cout << endl;
        //     for(int j = 0; j<avail_node; j++){
        //     if(leaves.find(j) == leaves.end())
        //       continue;
        //      cout <<dist[i][j] <<"\t";
        //    }
        //    }
        // cout << endl;
        if (leaves.size() == 3)
        {
            vector<int> v;
            v.clear();
            for (auto ver : leaves)
                v.push_back(ver);
            int a = v[0];
            int b = v[1];
            int c = v[2];
            pair<float, int> pairs[3];
            pairs[0] = make_pair(dist[a][par[a]], a);
            pairs[1] = make_pair(dist[b][par[b]], b);
            pairs[2] = make_pair(dist[c][par[c]], c);
            sort(pairs, pairs + 3);
            cout << "(";
            cout << name[pairs[0].second] << ", ";
            cout << name[pairs[1].second] << ", ";
            cout << name[pairs[2].second];
            cout << ");";
            cout << endl;
            break;
        }
        pair<float, float> min_dest = mp(DIST_MAX, DIST_MAX);
        pair<int, int> min_v = mp(-1, -1);
        for (auto v1 : leaves)
            for (auto v2 : leaves)
                if (v1 != v2 && par[v1] == par[v2] && mp(dist[v1][par[v1]], dist[v2][par[v2]]) < min_dest)
                    min_v = mp(v1, v2), min_dest = mp(dist[v1][par[v1]], dist[v2][par[v2]]);
        int parent = par[min_v.fi];
        name[parent] = "(" + name[min_v.fi] + "," + name[min_v.se] + ")";
        //cout << name[parent] << " " << name[min_v.fi] << " " << min_dest.fi << " " << name[min_v.se] << " " << min_dest.se << endl;
        edge[min_v.fi][parent] = edge[parent][min_v.fi] = 0;
        edge[min_v.se][parent] = edge[parent][min_v.se] = 0;
    }
}
