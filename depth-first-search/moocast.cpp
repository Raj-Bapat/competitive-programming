//
//  main.cpp
//  moocast-gold
//
//  Created by r on 11/25/17.
//  Copyright © 2017 r. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <fstream>
#include <cstring>
using namespace std;

pair<int, int> cows[1010];
int N;
int nfound = 0;
bool visited[1010];
int x;

void dfs(int node) {
    visited[node] = true;
    nfound++;
    for (int i = 0; i<N; i++) {
        if (!visited[i] && pow((cows[node].first-cows[i].first),2)+pow((cows[node].second-cows[i].second),2)<=x) {
            visited[node] = true;
            dfs(i);
        }
    }
}

int main(int argc, const char * argv[]) {
    ifstream fin;
    ofstream fout;
    fin.open("moocast.in");
    fout.open("moocast.out");
    fin >> N;
    for (int i = 0; i<N; i++) {
        fin >> cows[i].first >> cows[i].second;
    }
    int lo = 1, hi = pow(25000, 2);
    while (lo<hi) {
        memset(visited, 0, sizeof(visited));
        int mid = (lo+hi)/2;
        x = mid;
        nfound = 0;
        dfs(0);
        if (nfound==N) {
            hi = mid;
        } else {
            lo = mid+1;
        }
    }
    fout << lo << endl;
    return 0;
}
