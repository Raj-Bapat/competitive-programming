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
#include <complex>
#include <string>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef double db;
typedef string str;

typedef pair<int, int> pi;
typedef pair<ll,ll> pl;
typedef pair<ld,ld> pd;
#define mp make_pair
#define f first
#define s second

typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<ld> vd;
typedef vector<str> vs;
typedef vector<pi> vpi;
typedef vector<pl> vpl;
typedef vector<pd> vpd;

#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rall(x) (x).rbegin(), (x).rend()
#define rsz resize
#define ins insert
#define ft front()
#define bk back()
#define pf push_front
#define pb push_back
#define eb emplace_back
#define lb lower_bound
#define ub upper_bound

#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define trav(a,x) for (auto a: x)



const int MOD = 1e9+7; // 998244353; // = (119<<23)+1
const int MX = 1e5+5;
const ll INF = 1e18;
const ld PI = 4*atan((ld)1);
const int dx[4] = {0,1,0,-1}, dy[4] = {1,0,-1,0};





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

ll t[MX*4];

void upd(ll curr, ll tl, ll tr, ll pos, ll val) {
    if (tl == tr && tl == pos) {
        t[curr]^=val;
    } else {
        ll tm = (tl+tr)/2;
        if (pos <= tm) {
            upd(curr*2, tl, tm, pos, val);
        } else {
            upd(curr*2+1, tm+1, tr, pos, val);
        }
        t[curr] = t[curr*2]^t[curr*2+1];
    }
}

ll qry(ll curr, ll tl, ll tr, ll l, ll r) {
    if (l > r) {
        return 0;
    }
    if (tl == l && tr == r) {
        return t[curr];
    } else {
        ll tm = (tl+tr)/2;
        return qry(curr*2, tl, tm, l, min(r, tm))^qry(curr*2+1, tm+1, tr, max(l, tm+1), r);
    }
}

ll N, Q, L;
vl adj[MX];
pair<ll, pl> queries[MX];
vl lcaToRt[MX]; // list of timestamps in which I need to keep track of path cost
map<ll, ll> lcaRt[MX]; // maps timestamp to path cost
vector<pl> routEnd[MX]; // list of query indicies concerning this vertex, along with lca
ll qryLCAs[MX]; // lca of a specific query, might not need this
vector<pl> updvals[MX]; // update the tree with a value, timestamp
ll lastval[MX]; // the last vaue of a specific node (used with updval)
ll ans[MX];

/*
 1. update segment tree with new upd values
 2. check if I am an LCA of anything and save values as needed into lcaRT
 3. check LCA's of myself and update answer
 4. go to children
 5. remove the new upd values
 */


void solve(ll u, ll p) {
    trav (a, updvals[u]) {
        upd(1, 1, Q, a.s, a.f);
    }
    trav (a, lcaToRt[u]) {
        lcaRt[u][a] = qry(1, 1, Q, 1, a);
    }
    trav (a, routEnd[u]) {
        ll LCA = a.s;
        ll quind = a.f;
        ans[quind]^=qry(1, 1, Q, 1, quind)^lcaRt[LCA][quind];
    }
    trav (v, adj[u]) {
        if (v != p) {
            solve(v, u);
        }
    }
    trav (a, updvals[u]) {
        upd(1, 1, Q, a.s, a.f);
    }
}


ll timer;
vector<ll> tin, tout;
vector<vector<ll>> up;

void dfs(ll v, ll p) {
    tin[v] = timer++;
    up[v][0] = p;
    for (ll i = 1; i <= L; i++)
        up[v][i] = up[up[v][i-1]][i-1];
    
    for (ll u : adj[v]) {
        if (u != p)
            dfs(u, v);
    }
    
    tout[v] = timer++;
}

bool is_ancetor(ll u, ll v)
{
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

ll lca(ll u, ll v) {
    if (is_ancetor(u, v))
        return u;
    if (is_ancetor(v, u))
        return v;
    for (ll i = L; i >= 0; i--) {
        if (!is_ancetor(up[u][i], v))
            u = up[u][i];
    }
    return up[u][0];
}

void preprocess(ll root) {
    tin.resize(N);
    tout.resize(N);
    timer = 0;
    L = ceil(log2(N));
    up.assign(N, vector<ll>(L + 1));
    dfs(root, root);
}



int main() {
    ifstream fin;
    ofstream fout;
    fin.open("cowland.in");
    fout.open("cowland.out");
    fin >> N >> Q;
    FOR (i, 1, N+1) {
        ll a;
        fin >> a;
        updvals[i].pb(mp(a, 1));
        lastval[i] = a;
    }
    F0R (i, N-1) {
        ll a, b;
        fin >> a >> b;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    N++;
    preprocess(1);
    Q++;
    FOR (i, 2, Q+1) {
        fin >> queries[i].f >> queries[i].s.f >> queries[i].s.s;
        if (queries[i].f == 2) {
            ll LCA = lca(queries[i].s.f, queries[i].s.s);
            lcaToRt[LCA].pb(i);
            qryLCAs[i] = LCA;
            routEnd[queries[i].s.f].pb({i, LCA});
            routEnd[queries[i].s.s].pb({i, LCA});
            ans[i] = lastval[LCA];
        } else {
            ll val = lastval[queries[i].s.f]^queries[i].s.s;
            lastval[queries[i].s.f] = queries[i].s.s;
            updvals[queries[i].s.f].pb(mp(val, i));
        }
    }
    solve(1, 0);
    FOR (i, 2, Q+1) {
        if (queries[i].f == 2) {
            fout << ans[i] << "\n";
        }
    }
    return 0;
}


