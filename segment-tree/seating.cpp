
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


int add(int a, int b) {
    a += b;
    if(a >= MOD) {
        a -= MOD;
    }
    return a;
}
int sub(int a, int b) {
    a -= b;
    if(a < 0) {
        a += MOD;
    }
    return a;
}

int mul(int a, int b) {
    return (a * b)%MOD;
}

void add_self(int& a, int b) {
    a = add(a, b);
}
void sub_self(int& a, int b) {
    a = sub(a, b);
}
void mul_self(int& a, int b) {
    a = mul(a, b);
}


const int MAXN = 500010;

int N, M;
int pre[4*MAXN], suf[4*MAXN], lazy[4*MAXN], t[4*MAXN];

void push(int curr, int tl, int tr) {
    int tm = (tl+tr)/2;
    if (lazy[curr] == 1) {
        lazy[curr*2] = 1;
        pre[curr*2] = tm-tl+1;
        suf[curr*2] = tm-tl+1;
        t[curr*2] = tm-tl+1;
        lazy[curr*2+1] = 1;
        pre[curr*2+1] = tr-tm;
        suf[curr*2+1] = tr-tm;
        t[curr*2+1] = tr-tm;
    } else if (lazy[curr] == 0) {
        lazy[curr*2] = 0;
        pre[curr*2] = 0;
        suf[curr*2] = 0;
        t[curr*2] = 0;
        lazy[curr*2+1] = 0;
        pre[curr*2+1] = 0;
        suf[curr*2+1] = 0;
        t[curr*2+1] = 0;
    }
    lazy[curr] = -1;
}

void upd(int curr, int tl, int tr, int l, int r, int val) {
    if (l > r) {
        return;
    }
    if (tl == l && tr == r) {
        lazy[curr] = val;
        pre[curr] = val*(tr-tl+1);
        suf[curr] = val*(tr-tl+1);
        t[curr] = val*(tr-tl+1);
    } else {
        push(curr, tl, tr);
        int tm = (tl+tr)/2;
        upd(curr*2, tl, tm, l, min(r, tm), val);
        upd(curr*2+1, tm+1, tr, max(l, tm+1), r, val);
        pre[curr] = pre[curr*2]+(pre[curr*2] == tm-tl+1 ? pre[curr*2+1] : 0);
        suf[curr] = suf[curr*2+1]+(suf[curr*2+1] == tr-tm ? suf[curr*2] : 0);
//                cout << tl << " " << tr << " " << pre[curr] << " " << suf[curr] << "\n";
        t[curr] = max(max(pre[curr], suf[curr]), pre[curr*2+1]+suf[curr*2]);
        t[curr] = max(max(t[curr*2], t[curr*2+1]), t[curr]);
    }
}

int qry(int curr, int tl, int tr, int sz) {
    if (tl == tr) {
        return t[curr];
    }
    push(curr, tl, tr);
    int tm = (tl+tr)/2;
//    pre[curr] = pre[curr*2]+(pre[curr*2] == tm-tl+1 ? pre[curr*2+1] : 0);
//    suf[curr] = suf[curr*2+1]+(suf[curr*2+1] == tr-tm ? suf[curr*2] : 0);
//    t[curr] = max(max(pre[curr], suf[curr]), pre[curr*2+1]+suf[curr*2]);
//    t[curr] = max(max(t[curr*2], t[curr*2+1]), t[curr]);
    if (t[curr*2]>=sz) {
        return qry(curr*2, tl, tm, sz);
    } else if (pre[curr*2+1]+suf[curr*2] >= sz) {
        return tm-suf[curr*2]+1;
    } else if (t[curr*2+1]>=sz) {
        return qry(curr*2+1, tm+1, tr, sz);
    } else {
        return 0;
    }
}


int main() {
    cin >> N >> M;
    memset(lazy, -1, sizeof(lazy));
    upd(1, 1, N, 1, N, 1);
    int cnt = 0;
    for (int i = 0; i<M; i++) {
        char t;
        cin >> t;
        if (t == 'A') {
            int d;
            cin >> d;
            int ind = qry(1, 1, N, d);
            if (ind != 0) {
                upd(1, 1, N, ind, ind+d-1, 0);
            } else {
                cnt++;
            }
        } else {
            int x, d;
            cin >> x >> d;
            upd(1, 1, N, x, d, 1);
        }
    }
    cout << cnt << "\n";
    return 0;
}



