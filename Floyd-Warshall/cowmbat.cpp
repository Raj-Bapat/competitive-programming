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
#define MOD 1000000007

typedef long long ll;


ll add(ll a, ll b) {
    a += b;
    if(a >= MOD) {
        a -= MOD;
    }
    return a;
}
ll sub(ll a, ll b) {
    a -= b;
    if(a < 0) {
        a += MOD;
    }
    return a;
}

ll mul(ll a, ll b) {
    return (a * b)%MOD;
}

void add_self(ll& a, ll b) {
    a = add(a, b);
}
void sub_self(ll& a, ll b) {
    a = sub(a, b);
}
void mul_self(ll& a, ll b) {
    a = mul(a, b);
}


ll dists[27][27];
ll dp[100010][27];
ll pref[100010][27];
string S;
ll N, M, K;

ll f(ll i, ll lt) {
    if (i == N) {
        return 0;
    }
    if (dp[i][lt] != -1) {
        return dp[i][lt];
    }
    dp[i][lt] = 1e13;
    for (ll j = 0; j<M; j++) {
        if (i+K-1 >= N) {
            continue;
        }
        ll fi = pref[i+K-1][j], se = (i == 0 ? 0 : pref[i-1][j]);
        dp[i][lt] = min(dp[i][lt], fi-se+f(i+K, j));
    }
    if (i != 0) {
        dp[i][lt] = min(dp[i][lt], dists[S[i]-'a'][lt]+f(i+1, lt));
    }
    return dp[i][lt];
}

int main() {
    ifstream fin;
    ofstream fout;
    fin.open("cowmbat.in");
    fout.open("cowmbat.out");
    fin >> N >> M >> K >> S;
    for (ll i = 0; i<M; i++) {
        for (ll j = 0; j<M; j++) {
            fin >> dists[i][j];
        }
    }
    for (ll k = 0; k<M; k++) {
        for (ll i = 0; i<M; i++) {
            for (ll j = 0; j<M; j++) {
                dists[i][j] = min(dists[i][j], dists[i][k] + dists[k][j]);
            }
        }
    }
    memset(dp, -1, sizeof(dp));
    for (ll i = 0; i<M; i++) {
        ll curr = dists[(S[0]-'a')][i];
        pref[0][i] = curr;
        for (ll j = 1; j<N; j++) {
            curr+=dists[(S[j]-'a')][i];
            pref[j][i] = curr;
        }
    }
    fout << f(0, M) << "\n";
    return 0;
}




