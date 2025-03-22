#include <iostream>
#include <queue>
#include <vector>
#include <bits/stdc++.h>
using namespace std;
const int N = 1005, M = 100005;
int n, m, cost[M], inqueue[N], uses[M], prv[N], Edge[N];
long long cnt, res, d[N];
vector<pair<int,int> > S[N];

void Enter() {
    scanf("%d%d", &n, &m);
    int u, v;
    for(int i=1; i<=m; ++i) {
        scanf("%d%d%d", &u, &v, &cost[i]);
        S[u].emplace_back(v, i);
        S[v].emplace_back(u, -i);
    }
}

bool FindPath() {
    queue<int> Q;
    for(int i=1; i<=n; ++i) d[i] = 1e12;
    d[1] = 0;
    Q.push(1);
    inqueue[1] = true;
    while (!Q.empty()) {
        int u = Q.front(); Q.pop();
        inqueue[u] = false;
        for(pair<int,int> e : S[u]) {
            int v = e.first, ed = e.second;
            if (ed > 0) {
                if (uses[ed] == -1) {
                    if (d[v] > d[u] - cost[ed]) {
                        d[v] = d[u] - cost[ed];
                        if (!inqueue[v]) {
                            inqueue[v] = true;
                            Q.push(v);
                        }
                        prv[v] = u;
                        Edge[v] = ed;
                    }
                }
                else if (uses[ed] == 0) {
                    if (d[v] > d[u] + cost[ed]) {
                        d[v] = d[u] + cost[ed];
                        if (!inqueue[v]) {
                            inqueue[v] = true;
                            Q.push(v);
                        }
                        prv[v] = u;
                        Edge[v] = ed;
                    }
                }
            }
            else {
                ed = -ed;
                if (uses[ed] == 1) {
                    if (d[v] > d[u] - cost[ed]) {
                        d[v] = d[u] - cost[ed];
                        if (!inqueue[v]) {
                            inqueue[v] = true;
                            Q.push(v);
                        }
                        prv[v] = u;
                        Edge[v] = -ed;
                    }
                }
                else if (uses[ed] == 0) {
                    if (d[v] > d[u] + cost[ed]) {
                        d[v] = d[u] + cost[ed];
                        if (!inqueue[v]) {
                            inqueue[v] = true;
                            Q.push(v);
                        }
                        prv[v] = u;
                        Edge[v] = -ed;
                    }
                }
            }
        }
    }
    return d[n] < 1e12;
}

void MaxFlow() {
    ++cnt; res += d[n];
    int u = n;
    while (u != 1) {
        int ed = Edge[u];
        if (ed > 0) ++uses[ed]; else --uses[-ed];
        u = prv[u];
    }
}

void Process() {
    if (n>1) while (FindPath()) MaxFlow();
    cout << cnt << ' ' << res;
}

int main()
{
    freopen("tourism.inp","r",stdin);
    freopen("tourism.out","w",stdout);
    Enter();
    Process();
}
