//
//  main.cpp
//  hps-gold
//
//  Created by r on 1/10/18.
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
// H 1;
// P 2
// S 3;


typedef char                b8;
typedef int                 b32;
typedef long long           b64;
typedef unsigned char           ub8;
typedef unsigned int        ub32;
typedef unsigned long long     ub64;

int addone(int gesture) {
    if (gesture == 3) {
        return 1;
    } else {
        return gesture+1;
    }
}

int subone(int gesture) {
    if (gesture == 1) {
        return 3;
    } else {
        return gesture-1;
    }
}


b32 dp[100010][30][4];
b32 fjmoves[100010];
int N,K;



int main(int argc, const char * argv[]) {
    ios_base :: sync_with_stdio(false);
    ifstream fin;
    ofstream fout;
    fin.open("hps.in");
    fout.open("hps.out");
    fin >> N >> K;
    for (int i = 0; i<N; i++) {
        b8 ch;
        fin >> ch;
        if (ch == 'H') {
            fjmoves[i] = 1;
        } else if (ch == 'P') {
            fjmoves[i] = 2;
        } else {
            fjmoves[i] = 3;
        }
    }
    memset(dp, -1, sizeof(dp));
    memset(dp[N], 0, sizeof(dp[N]));
    for (int i = 0; i<=N; i++) {
        for (int k = 0; k<4; k++) {
            dp[i][K+1][k] = numeric_limits<int>::min();
        }
    }
    for (int i = N-1; i>=0; i--) {
        for (int cs = K; cs>=0; cs--) {
            for (int cg = 3; cg>=1; cg--) {
                if (fjmoves[i] == subone(cg)) {
                    dp[i][cs][cg] = 1+dp[i+1][cs][cg];
                } else if (fjmoves[i] == addone(cg)) {
                    dp[i][cs][cg] = max(dp[i+1][cs][cg], max(1+dp[i+1][cs+1][subone(cg)], dp[i+1][cs+1][addone(cg)]));
                } else {
                    dp[i][cs][cg] = max(dp[i+1][cs][cg], max(dp[i+1][cs+1][subone(cg)], 1+dp[i+1][cs+1][addone(cg)]));
                }
            }
        }
    }
    fout << max(dp[0][0][1], max(dp[0][0][2], dp[0][0][3])) << endl;
    return 0;
}
