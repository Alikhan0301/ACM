// nlog^2
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

#include <unordered_map>

using namespace std;

#define all(x) (x).begin(),(x).end()
#define ll long long
#define pii pair<int,int>
#define f first
#define s second
#define y1 Emilia
#define N 400400
#define dracarys ios_base :: sync_with_stdio(0);cin.tie(0);cout.tie(0);



int n, Q;
int all, cnt = 1;
int sz[N], depth[N], nxt[N], chain[N], top[N], pos[N], pa[N];
ll t[4 * N];
vector<int> g[N];

void upd (int v, int tl, int tr, int pos, int val) {
    if (tl == tr)
        t[v] += val;
    else {
        int mid = (tl + tr) >> 1;
        if (pos <= mid)
            upd (v + v, tl, mid, pos, val);
        else
            upd (v + v + 1, mid + 1, tr, pos, val);
        
        t[v] = max (t[v + v], t[v + v + 1]);
    }
}

ll get_max (int v, int tl, int tr, int l, int r) {
    if (tr < l || r < tl)
        return 0;
    if (l <= tl && tr <= r)
        return t[v];
    
    int mid = (tl + tr) >> 1;
    
    return max (get_max(v + v, tl, mid, l, r), get_max (v + v + 1, mid + 1, tr, l, r));
}

void calc (int v, int p) {
    pa[v] = p;
    sz[v] = 1;
    nxt[v] = -1;
    
    for (int to : g[v]) {
        if (to == p)
            continue;
        
        depth[to] = depth[v] + 1;
        calc (to, v);
        
        sz[v] += sz[to];
        if (nxt[v] == -1 || sz[to] > sz[nxt[v]])
            nxt[v] = to;
    }
}

void hld (int v, int p) {
    chain[v] = cnt;
    pos[v] = ++all;
    if (top[chain[v]] == 0)
        top[chain[v]] = v;
    
    if (nxt[v] != -1)
        hld (nxt[v], v);
    
    for (int to : g[v]) {
        if (to == p || to == nxt[v])
            continue;
        ++cnt;
        hld (to, v);
    }
}

ll get_answer (int a, int b) {
    ll res = 0;
    while (chain[a] != chain[b]) {
        if (depth[top[chain[a]]] < depth[top[chain[b]]])
            swap (a, b);
        
        int start = top[chain[a]];
        res = max (res, get_max (1, 1, n, pos[start], pos[a]));
        
        a = pa[start];
    }
    
    if (depth[a] < depth[b])
        swap (a, b);
    
    res = max (res, get_max (1, 1, n, pos[b], pos[a]));
    return res;
}

int main(){
    dracarys
    
    cin >> n;
    
    for (int i = 1; i <= n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    
    calc (1, 0);
    
    hld (1, 0);
    
    cin >> Q;
    
    while (Q--)
    {
        char type;
        int u, v;
        cin >> type >> u >> v;
        
        if (type == 'I')
            upd (1, 1, n, pos[u], v);
        else
            cout << get_answer (u, v) << "\n";
    }
    return 0;
}
