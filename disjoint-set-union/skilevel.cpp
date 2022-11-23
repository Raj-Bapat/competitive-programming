
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


const ll MAXN = 510;

ll diff[MAXN][MAXN];
int hold[MAXN][MAXN];
ll N, M, T, E = 0;
pair<ll, pair<int, int>> edges[1000010];
int nodes = 0;
int parent[300010];
int nrank[300010];
int sz[300010];
vector<pair<int, int>> sp;
ll best[300010];

void create_set() {
    nodes++;
    parent[nodes] = nodes;
    nrank[nodes] = 0;
    sz[nodes] = 1;
    best[nodes] = -1;
}


ll find_set(ll x) {
    if (parent[parent[x]] != parent[x]) {
        find_set(parent[x]);
    }
    if (best[x] == -1) {
        if (best[parent[x]] != -1) {
            best[x] = best[parent[x]];
        } else {
            best[x] = best[parent[parent[x]]];
        }
    }
    parent[x] = parent[parent[x]];
    return parent[x];
}

void merge_sets(ll x, ll y) {
    ll PX = find_set(x), PY = find_set(y);
    assert(PX == x && PY == y);
    if (nrank[PX] > nrank[PY]) {
        parent[PY] = PX;
        sz[PX]+=sz[PY];
    } else {
        parent[PX] = PY;
        sz[PY]+=sz[PX];
    }
    if (nrank[PX] == nrank[PY]) {
        nrank[PY]++;
    }
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> M >> T;
    ll curr = 1;
    for (ll i = 1; i<=N; i++) {
        for (ll j = 1; j<=M; j++) {
            hold[i][j] = curr;
            curr++;
        }
    }
    for (ll i = 1; i<=N; i++) {
        for (ll j = 1; j<=M; j++) {
            cin >> diff[i][j];
        }
    }
    for (ll i = 1; i<=N; i++) {
        for (ll j = 1; j<=M; j++) {
            ll a;
            cin >> a;
            if (a == 1) {
                sp.push_back({i, j});
            }
        }
    }
    for (ll i = 1; i<=N; i++) {
        for (ll j = 1; j<=M; j++) {
            if (i>1) {
                edges[E] = {abs(diff[i][j]-diff[i-1][j]), {hold[i][j], hold[i-1][j]}};
                E++;
            }
            if (i<N) {
                edges[E] = {abs(diff[i][j]-diff[i+1][j]), {hold[i][j], hold[i+1][j]}};
                E++;
            }
            if (j>1) {
                edges[E] = {abs(diff[i][j]-diff[i][j-1]), {hold[i][j], hold[i][j-1]}};
                E++;
            }
            if (j<M) {
                edges[E] = {abs(diff[i][j]-diff[i][j+1]), {hold[i][j], hold[i][j+1]}};
                E++;
            }
        }
    }
    ll ans = 0;
    for (ll i = 1; i<=hold[N][M]; i++) {
        create_set();
    }
    sort(edges, edges+E);
    for (ll i = 0; i<E; i++) {
        ll u = find_set(edges[i].second.first);
        ll v = find_set(edges[i].second.second);
        if (u != v) {
            if (sz[u]+sz[v] >= T) {
                if (sz[u] < T) {
                    best[u] = edges[i].first;
                }
                if (sz[v] < T) {
                    best[v] = edges[i].first;
                }
            }
            merge_sets(u, v);
        }
    }
    for (ll i = 0; i<sp.size(); i++) {
        find_set(hold[sp[i].first][sp[i].second]);
        ans+=best[hold[sp[i].first][sp[i].second]];
    }
    
    cout << ans << "\n";
    return 0;
}
                
                
                
