//
//  main.cpp
//  piggyback
//
//  Created by r on 11/18/17.
//  Copyright © 2017 r. All rights reserved.
//


#include <iostream>
#include <algorithm>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <stack>
#include <queue> 
#include <assert.h>
#include <limits>
using namespace std;

//#define RDEBUG 1
#ifdef RDEBUG
#define D(x) x
#else
#define D(x)
#endif
#define inf 0x7fffffff

int B, E, P, N, M;
vector<int> adjlist[40010];
int sps[4][40010];
bool visited[40010];

void bfs(int a, int energy, int start) {
    queue<int> q;
    q.push(start);
    q.push(0);
    sps[a][start] = 0;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        int e = q.front();
        q.pop();
        if (visited[node]) {
            continue;
        }
        visited[node] = true;
        sps[a][node] = e;
        for (int i = 0; i<adjlist[node].size(); i++) {
            if (!visited[adjlist[node][i]]) {
                q.push(adjlist[node][i]);
                q.push(e+energy);
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    ifstream fin;
    ofstream fout;
    fin.open("piggyback.in");
    fout.open("piggyback.out");
    ios_base :: sync_with_stdio(false);
    fin >> B >> E >> P >> N >> M;
    for (int i = 0; i<M; i++) {
        int u,v;
        fin >> u >> v;
        adjlist[u].push_back(v);
        adjlist[v].push_back(u);
    }
    bfs(1, B, 1);
    memset(visited, 0, sizeof(visited));
    bfs(2, E, 2);
    memset(visited, 0, sizeof(visited));
    bfs(3, P, N);
    int minenergy = sps[1][N]+sps[2][N];
    for (int i = 1; i<=N; i++) {
        minenergy = min(minenergy, sps[1][i]+sps[2][i]+sps[3][i]);
    }
    fout << minenergy << endl;
    return 0;
}

