//
//  main.cpp
//  cownomics-gold
//
//  Created by r on 1/8/18.
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
#include <map>
#include <unordered_map>
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

char sgenes[510][510];
char pgenes[510][510];
unsigned long long ppow[510];
int N,M;
int good[510];
#define B 31

bool alldist(int len) {
    memset(good, 0, sizeof(good));
    vector<unordered_set<unsigned long long>> hashes(M);
    for (int i = 0; i<N; i++) {
        memset(ppow,0,sizeof(ppow));
        unsigned long long currhash = 0;
        ppow[len-1] = 1;
        for (long long j = len-2; j>=0; j--) {
            ppow[j] = B*ppow[j+1];
            D(cout << ppow[i] << " ");
        }
        for (long long j = len-1; j>=0; j--) {
            currhash += (sgenes[i][j]-'a'+1)*ppow[j];
        }
        hashes[0].insert(currhash);
        for (int j = len; j<M; j++) {
            unsigned long long asdf = (currhash-((sgenes[i][j-len]-'a'+1)*ppow[0]));
            currhash = asdf*B+(sgenes[i][j]-'a'+1);
            hashes[j-len+1].insert(currhash);
        }
    }
    for (int i = 0; i<N; i++) {
        memset(ppow,0,sizeof(ppow));
        unsigned long long currhash = 0;
        ppow[len-1] = 1;
        for (long long j = len-2; j>=0; j--) {
            ppow[j] = B*ppow[j+1];
            D(cout << ppow[i] << " ");
        }
        for (long long j = len-1; j>=0; j--) {
            currhash += (pgenes[i][j]-'a'+1)*ppow[j];
        }
        for (int j = len; j<M; j++) {
            unsigned long long asdf = (currhash-((pgenes[i][j-len]-'a'+1)*ppow[0]));
            currhash = asdf*B+(pgenes[i][j]-'a'+1);
            if (hashes[j-len+1].find(currhash) == hashes[j-len+1].end()) {
                good[j-len+1]++;
                if (good[j-len+1] == N) {
                    return true;
                }
            }
        }
    }
    return false;
}



int main(int argc, const char * argv[]) {
    ios_base :: sync_with_stdio(false);
    ifstream fin;
    ofstream fout;
    fin.open("cownomics.in");
    fout.open("cownomics.out");
    fin >> N >> M;
    for (int i = 0; i<N; i++) {
        for (int j = 0; j<M; j++) {
            char ch;
            fin >> ch;
            sgenes[i][j] = tolower(ch);
        }
    }
    for (int i = 0; i<N; i++) {
        for (int j = 0; j<M; j++) {
            char ch;
            fin >> ch;
            pgenes[i][j] = tolower(ch);
        }
    }
    int lo = 1, hi = M;
    while (lo<hi) {
        int mid = (lo+hi)/2;
        if (alldist(mid)) {
            hi = mid;
        } else {
            lo = mid+1;
        }
    }
    fout << lo << endl;
    return 0;
}



