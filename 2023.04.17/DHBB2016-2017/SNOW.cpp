#include <bits/stdc++.h>
#define pow2(i) (1 << (i))
#define MAXN 101
#define MAXK 10
#define make_(i,j,k) make_pair(i,make_pair(j,k))
#define INF 1000000000
using namespace std;

int32_t n,k,m,type;
vector <pair < int32_t, pair <int32_t,int32_t> > > edge;
int32_t f[MAXN][MAXN];
int32_t d[MAXN][pow2(MAXK)];
int32_t t[MAXK];
bool chosen_vertex[MAXN];
int32_t n_chosen_vertex;
int32_t min_steiner_tree;
int32_t fa[MAXN];
int32_t mask[MAXN];
priority_queue <pair <int32_t, pair <int32_t,int32_t> > > heap;

int32_t to_bitmask(int i)
{
    if (mask[i] < 0) return 0;
    return pow2(mask[i]);
}

void type1()
{
    min_steiner_tree = INF;
    for (int32_t l = 0; l < n; ++l)
        for (int32_t i = 0; i < n; ++i)
            for (int32_t j = 0; j < n; ++j)
                if (f[i][j] > f[i][l] + f[l][j])
                    f[i][j] = f[i][l] + f[l][j];
    for (int32_t i = 0; i < n; ++i)
        for (int32_t j = 0; j < pow2(k); ++j)
            d[i][j] = INF;
    for (int32_t i = 0; i < n; ++i)
    {
        heap.push(make_(0,i,to_bitmask(i)));
        d[i][to_bitmask(i)] = 0;
    }
    int32_t u,bit_mask,s,new_bit_mask;
    while(!heap.empty())
    {
        s = -heap.top().first;
        u = heap.top().second.first;
        bit_mask = heap.top().second.second;
        heap.pop();
        //cout << s << " " << u << " " << bit_mask << endl;
        if (s > d[u][bit_mask]) continue;
        if (bit_mask == pow2(k) - 1)
        {
            min_steiner_tree = s;
            break;
        }
        for (int32_t v = 0; v < n; ++v)
        {
            new_bit_mask = bit_mask | to_bitmask(v);
            if (d[v][new_bit_mask] > d[u][bit_mask] + f[u][v])
            {
                d[v][new_bit_mask] = d[u][bit_mask] + f[u][v];
                heap.push(make_(-d[v][new_bit_mask],v,new_bit_mask));
            }
            if (d[u][new_bit_mask] > d[u][bit_mask] + f[u][v])
            {
                d[u][new_bit_mask] = d[u][bit_mask] + f[u][v];
                heap.push(make_(-d[u][new_bit_mask],u,new_bit_mask));
            }
        }
        for (int32_t i = 0; i < pow2(k); ++i)
            if (d[u][i]+ d[u][bit_mask] < d[u][i | bit_mask])
            {
                //cerr << s << " " << u << " " << bit_mask << " " << i << endl;
                d[u][i | bit_mask] = d[u][i]+ d[u][bit_mask];
                heap.push(make_(-d[u][i | bit_mask],u,i | bit_mask));
            }
    }
    cout << min_steiner_tree << endl;
}

int32_t root(int32_t u)
{
    int32_t v = u;
    while (fa[u] != -1)
        u = fa[u];
    if (u != v) fa[v] = u;
    return u;
}

int32_t get_min_spanning_tree()
{
    int32_t sum = 0;
    int32_t cnt = 1;
    int32_t u,v,w,ru,rv;
    memset(fa,-1,sizeof(fa));
    for (int32_t i = 0; i < m; ++i)
    {
        w = edge[i].first;
        u = edge[i].second.first;
        v = edge[i].second.second;
        if (chosen_vertex[u] && chosen_vertex[v])
        {
            ru = root(u);
            rv = root(v);
            if (ru != rv)
            {
                ++cnt;
                fa[ru] = rv;
                sum += w;
            }
        }
    }
    if (cnt == n_chosen_vertex) return sum;
    return INF;
}

void chose(int32_t i)
{
    if (i == k)
    {
        min_steiner_tree = min(min_steiner_tree,get_min_spanning_tree());
        return;
    }
    chosen_vertex[t[i]] = true;
    ++n_chosen_vertex;
    chose(i+1);
    --n_chosen_vertex;
    chosen_vertex[t[i]] = false;
    chose(i+1);
}

void type2()
{
    sort(edge.begin(),edge.end());
    min_steiner_tree = INF;
    memset(chosen_vertex,true,sizeof(chosen_vertex));
    for (int i = 0; i < k; ++i)
        chosen_vertex[t[i]] = false;

    n_chosen_vertex = n - k;
    chose(0);
    cout << min_steiner_tree << endl;
}

int32_t main()
{
    freopen("snow.inp","r",stdin);
    freopen("snow.out","w",stdout);
    cin >> n >> k >> m >> type;

    memset(mask,-1,sizeof(mask));
    for (int32_t i = 0; i < k; ++i)
    {
        cin >> t[i];
        --t[i];
        mask[t[i]] = i;
    }

    if (k==n) {
    	type = 2;
    	k = 0;		
    }

    int u,v,w;
    for (int32_t i = 0; i < n; ++i)
        for(int32_t j = 0; j < n; ++j)
            if (i != j)
                f[i][j] = INF;
    for (int32_t i = 0; i < m; ++i)
    {
        cin >> u >> v >> w;
        --u;--v;
        edge.push_back(make_pair(w,make_pair(u,v)));
        f[u][v] = w;
        f[v][u] = w;
    }
    if (type == 1) type1();
    else type2();
    return 0;
}
