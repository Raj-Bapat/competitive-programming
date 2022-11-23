/*
 ID: a2g2gon1
 PROG: agrinet
 LANG: C++11
 */
//
//  main.cpp
//  agrinet
//
//  Created by r on 4/25/17.
//  Copyright © 2017 r. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <unordered_set>
#include <limits>
using namespace std;

int dists[101][101];
int N;
unordered_set<int> visited;

int main(int argc, const char * argv[]) {
    ifstream fin;
    ofstream fout;
    fin.open("agrinet.in");
    fout.open("agrinet.out");
    cin >> N;
    for (int i = 0; i<N; i++) {
        for (int j = 0; j<N; j++) {
            cin >> dists[i][j];
        }
    }
    for (int i = 0; i<N; i++) {
        dists[i][i] = numeric_limits<int>::max();
    }
    int len = 0;
    visited.insert(0);
    while (visited.size()!=N) {
        int mv = 0, mind = numeric_limits<int>::max();
        for (int i = 0; i<N; i++) {
            if (visited.find(i) != visited.end()) {
                for (int j = 0; j<N; j++) {
                    if (visited.find(j) == visited.end() && dists[i][j]<mind) {
                        mind = dists[i][j];
                        mv = j;
                    }
                }
            }
        }
        len+=mind;
        visited.insert(mv);
    }
    cout << len << endl;
    return 0;
}
