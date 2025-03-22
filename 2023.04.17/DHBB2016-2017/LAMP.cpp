#include <bits/stdc++.h>
#define MAXN 100007
using namespace std;

int32_t n,m;
int32_t r[MAXN], b[MAXN];
int64_t n_triangle,n_diff_color_triangle;
map < pair <int32_t, int32_t> , bool > color; // xac dinh mau cua canh i,j

bool get_color(pair<int32_t,int32_t> c)
{
    // true neu canh (i,j) co mau xanh, false neu mau do
    if (color.count(c) == 0) return true;
    return color[c];
}

int main()
{
    freopen("lamp.inp","r",stdin);
    freopen("lamp.out","w",stdout);
    cin >> n >> m;
    //ban dau tat ca cac canh deu mau xanh
    for (int i = 1; i <= n; ++i)
        b[i] = n-1;
    n_triangle = (int64_t) n * (n-1) * (n-2) / 6;
    int32_t x,y;
    bool pre_color;
    for(int32_t i = 0; i < m; ++i)
    {
        cin >> x >> y;
        if (x > y) swap (x,y);
        //if (x == y) cout << i << endl;
        pre_color = get_color(make_pair(x,y));
        n_diff_color_triangle -= (r[x] * b[x] + r[y] * b[y]);
        if(pre_color)
        {
            --b[x];--b[y];
            ++r[x];++r[y];
        }
        else
        {
            ++b[x];++b[y];
            --r[x];--r[y];
        }
        n_diff_color_triangle += (r[x] * b[x] + r[y] * b[y]);
        color[make_pair(x,y)] = !pre_color;
        cout << n_triangle - n_diff_color_triangle / 2 << endl;
    }
    return 0;
}
