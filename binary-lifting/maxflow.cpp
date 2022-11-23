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
#define trav(a,x) for (auto& a: x)

const int MOD = 1e9+7; // 998244353; // = (119<<23)+1
const int MX = 2e5+5;
const ll INF = 1e18;
const ld PI = 4*atan((ld)1);
const int dx[4] = {0,1,0,-1}, dy[4] = {1,0,-1,0};


namespace io {
    void setIn(string s) { freopen(s.c_str(),"r",stdin); }
    void setOut(string s) { freopen(s.c_str(),"w",stdout); }
    void setIO(string s = "") {
        ios_base::sync_with_stdio(0); cin.tie(0); // fast I/O
        // cin.exceptions(cin.failbit); // ex. throws exception when you try to read letter into int
        if (sz(s)) {
            setIn(s+".in");
            setOut(s+".out");
        } // for USACO
    }
}

using namespace io;

namespace input {
    template<class T> void re(complex<T>& x);
    template<class T1, class T2> void re(pair<T1,T2>& p);
    template<class T> void re(vector<T>& a);
    template<class T, size_t SZ> void re(array<T,SZ>& a);
    
    template<class T> void re(T& x) { cin >> x; }
    void re(double& x) { string t; re(t); x = stod(t); }
    void re(ld& x) { string t; re(t); x = stold(t); }
    template<class Arg, class... Args> void re(Arg& first, Args&... rest) {
        re(first); re(rest...);
    }
    
    template<class T> void re(complex<T>& x) { T a,b; re(a,b); x = cd(a,b); }
    template<class T1, class T2> void re(pair<T1,T2>& p) { re(p.f,p.s); }
    template<class T> void re(vector<T>& a) { F0R(i,sz(a)) re(a[i]); }
    template<class T, size_t SZ> void re(array<T,SZ>& a) { F0R(i,SZ) re(a[i]); }
}

namespace output {
    template<class T1, class T2> void pr(const pair<T1,T2>& x);
    template<class T, size_t SZ> void pr(const array<T,SZ>& x);
    template<class T> void pr(const vector<T>& x);
    template<class T> void pr(const set<T>& x);
    template<class T1, class T2> void pr(const map<T1,T2>& x);
    
    template<class T> void pr(const T& x) { cout << x; }
    template<class Arg, class... Args> void pr(const Arg& first, const Args&... rest) {
        pr(first); pr(rest...);
    }
    
    template<class T1, class T2> void pr(const pair<T1,T2>& x) {
        pr("{",x.f,", ",x.s,"}");
    }
    template<class T> void prContain(const T& x) {
        pr("{");
        bool fst = 1; for (const auto& a: x) pr(!fst?", ":"",a), fst = 0; // const needed for vector<bool>
        pr("}");
    }
    template<class T, size_t SZ> void pr(const array<T,SZ>& x) { prContain(x); }
    template<class T> void pr(const vector<T>& x) { prContain(x); }
    template<class T> void pr(const set<T>& x) { prContain(x); }
    template<class T1, class T2> void pr(const map<T1,T2>& x) { prContain(x); }
    
    void ps() { pr("\n"); }
    template<class Arg> void ps(const Arg& first) {
        pr(first); ps(); // no space at end of line
    }
    template<class Arg, class... Args> void ps(const Arg& first, const Args&... rest) {
        pr(first," "); ps(rest...); // print w/ spaces
    }
}

using namespace output;

using namespace input;

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

ll K;
ll N, L;
vector<ll> adj[MX];

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

ll postorder[MX];
ll curr = 0;
ll par[MX];
ll lazy[MX];
ll pref[MX];

void getOrder(ll u, ll p) {
    par[u] = p;
    trav(v, adj[u]) {
        if (v != p) {
            getOrder(v, u);
        }
    }
    postorder[curr] = u;
    curr++;
}


int main() {
    setIO("maxflow");
    re(N, K);
    F0R (i, N-1) {
        ll a, b;
        re(a, b);
        a--;
        b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    preprocess(0);
    getOrder(0, -1);
    F0R (i, K) {
        ll a, b;
        re(a, b);
        a--;
        b--;
        ll c = lca(a, b);
        lazy[a]++;
        lazy[b]++;
        lazy[c]--;
        if (c != 0) {
            lazy[par[c]]--;
        }
    }
    ll best = -1;
    F0R (i, N) {
        ll u = postorder[i];
        pref[u]+=lazy[u];
        best = max(best, pref[u]);
        if (u != 0) {
            pref[par[u]]+=pref[u];
        }
    }
    ps(best);
    return 0;
}


