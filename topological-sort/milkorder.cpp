//
//  main.cpp
//  milkorder3
//
//  Created by r on 10/7/18.
//  Copyright © 2018 r. All rights reserved.
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
#include <unordered_map>
#include <map>
#include <stack>
#include <queue>
#include <assert.h>
#include <limits>
#include <cstdio>
using namespace std;

//#define RDEBUG 1
#ifdef RDEBUG
#define D(x) x
#else
#define D(x)
#endif
#define inf 0x7fffffff

int N,M;

vector<pair<int, int>> adjlist[100010];
int visited[100010];
int indeg[100010];
int currmid = 0;
int hascycle = 0;

void dfs(int n) {
    visited[n] = 1;
    for (int i = 0; i<adjlist[n].size(); i++) {
        pair<int, int> v = adjlist[n][i];
        if (v.second>currmid || visited[v.first] == 2) {
            continue;
        }
        if (visited[v.first] == 1) {
            hascycle = 1;
            continue;
        }
        visited[v.first] = 1;
        dfs(v.first);
    }
    visited[n] = 2;
}

int main(int argc, const char * argv[]) {
    ifstream fin;
    ofstream fout;
    fin.open("milkorder.in");
    fout.open("milkorder.out");
    fin >> N >> M;
    for (int i = 0; i<M; i++) {
        int ci;
        fin >> ci;
        int curr;
        fin >> curr;
        for (int j = 0; j<ci-1; j++) {
            int nextj;
            fin >> nextj;
            adjlist[curr].push_back(make_pair(nextj, i));
            curr = nextj;
        }
    }
    int lo = 0, hi = M-1;
    while (lo<hi) {
        int mid = (lo+hi+1)/2;
        currmid = mid;
        hascycle = 0;
        memset(visited, 0, sizeof(visited));
        for (int i = 1; i<=N; i++) {
            if (!visited[i]) {
                dfs(i);
            }
        }
        if (hascycle) {
            hi = mid-1;
        } else {
            lo = mid;
        }
    }
    set<int> q;
    for (int i = 1; i<=N; i++) {
        for (int j = 0; j<adjlist[i].size(); j++) {
            if (adjlist[i][j].second<=lo) {
                indeg[adjlist[i][j].first]++;
            }
        }
    }
    for (int i = 1; i<=N; i++) {
        if (indeg[i] == 0) {
            q.insert(i);
        }
    }
    vector<int> ans;
    while (!q.empty()) {
        int curr = *q.begin();
        q.erase(q.begin());
        ans.push_back(curr);
        for (int i = 0; i<adjlist[curr].size(); i++) {
            if (adjlist[curr][i].second<=lo) {
                indeg[adjlist[curr][i].first]--;
                if (!indeg[adjlist[curr][i].first]) {
                    q.insert(adjlist[curr][i].first);
                }
            }
        }
    }
    for (int i = 0; i<ans.size()-1; i++) {
        fout << ans[i] << " ";
    }
    fout << ans[ans.size()-1] << endl;
    return 0;
}
