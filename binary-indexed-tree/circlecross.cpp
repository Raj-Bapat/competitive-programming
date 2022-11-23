//
//  main.cpp
//  circlecross-bit
//
//  Created by r on 12/10/17.
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

int tree[400010];
int events[100010];
int N;


void addtotree(long long num, long long ind) {
    long long j = ind;
    while (j<=N) {
        tree[j]+=num;
        j+=(j&-j);
    }
}

long long getval(long long j) {
    long long sum = 0;
    while (j) {
        sum+=tree[j];
        j-=(j&-j);
    }
    return sum;
}

int main(int argc, const char * argv[]) {
    ifstream fin;
    ofstream fout;
    fin.open("circlecross.in");
    fout.open("circlecross.out");
    fin >> N;
    N*=2;
    vector<pair<int, int>> line(N/2+1);
    for (int i = 0; i<=N; i++) {
        line[i].first = -1;
        line[i].second = -1;
    }
    for (int i = 0; i<N; i++) {
        fin >> events[i];
    }
    for (int i = 0; i<N; i++) {
        if (line[events[i]].first == -1) {
            line[events[i]].first = i;
        } else {
            line[events[i]].second = i;
        }
    }
    
    sort(begin(line)+1, begin(line)+N/2+1);
    int crossings = 0;
    for (int i = 1; i<=N/2; i++) {
        crossings+=getval(line[i].second)-getval(line[i].first);
        addtotree(1, line[i].second);
    }
    cout << "reached" << endl;
    fout << crossings << endl;
    return 0;
}
