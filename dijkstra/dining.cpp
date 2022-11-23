//
//  main.cpp
//  dining-2nd
//
//  Created by r on 12/23/18.
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

vector<pair<long long, long long>> adj[200010];
long long sp[200010];
long long sp2[200010];
long long V,E,K;
pair<long long, long long> bales[200010];
unordered_map<long long, long long> seee;

bool isfirst = true;

void dijkstra(long long s) {
    using pii = pair<long long, long long>;
    priority_queue<pii, vector<pii>, greater<pii>> q;
    if (isfirst) {
        sp[V] = 0;
        q.push({0, s});
    } else {
        for (int ii = 0; ii<K; ii++) {
            long long ss = bales[ii].first;
            sp[ss] = sp2[ss] - bales[ii].second;
            q.push({sp[ss], ss});
        }
    }
    while (!q.empty()) {
        long long v = q.top().second;
        long long d_v = q.top().first;
        q.pop();
        if (d_v != sp[v]) {
            continue;
        }
        for (auto edge : adj[v]) {
            long long to = edge.first;
            long long len = edge.second;
            if (sp[v] + len < sp[to]) {
                sp[to] = sp[v] + len;
                q.push({sp[to], to});
            }
        }
    }
}


int main(int argc, const char * argv[]) {
    ifstream fin;
    ofstream fout;
    fin.open("dining.in");
    fout.open("dining.out");
    fin >> V >> E >> K;
    for (int i = 0; i<200010; i++) {
        sp[i] = numeric_limits<long long>::max();
        sp2[i] = numeric_limits<long long>::max();
    }
    for (int i = 0; i<E; i++) {
        long long f,s,t;
        fin >> f >> s >> t;
        adj[f].push_back(make_pair(s, t));
        adj[s].push_back(make_pair(f, t));
    }
    for (int i = 0; i<K; i++) {
        long long f, s;
        fin >> f >> s;
        if (seee.find(f) == seee.end()) {
            bales[i] = make_pair(f, s);
            seee[f] = i;
        } else {
            assert(0);
            K--;
            i--;
            if (bales[seee[f]].second<s) {
                bales[seee[f]].second = s;
            }
        }
    }
    dijkstra(V);
    for (int i = 1; i<=V; i++) {
        sp2[i] = sp[i];
    }
    for (int i = 0; i<200010; i++) {
        sp[i] = numeric_limits<long long>::max();
    }
    isfirst = false;
    dijkstra(V);
    for (int i = 1; i<V; i++) {
        if (sp[i] != numeric_limits<long long>::max() && sp[i]<=sp2[i]) {
            fout << 1 << endl;
        } else {
            fout << 0 << endl;
        }
    }
    return 0;
}




