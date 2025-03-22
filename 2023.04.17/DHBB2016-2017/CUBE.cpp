#include <bits/stdc++.h>
#define MAX_N 5
#define MAX_SIZE 32
#define pow2(i) (1 << (i))
using namespace std;

int32_t n,i,j,k;
int32_t a[MAX_SIZE][MAX_SIZE][MAX_SIZE];
int32_t cnt;

bool inside(int32_t n, int32_t i, int32_t j, int32_t k)
{
    if ((i < 0) || (j < 0) || (k < 0) || (i >= pow2(n)) || (j >= pow2(n)) || (k >= pow2(n))) return false;
    return true;
}

void Fill(int32_t n, int32_t i, int32_t j, int32_t k, int32_t si, int32_t sj, int32_t sk)
{
    if (n == 1)
    {
        ++cnt;
        for (int32_t li = 0; li < 2; ++li)
        for (int32_t lj = 0; lj < 2; ++lj)
        for (int32_t lk = 0; lk < 2; ++lk)
            if ((li != i) || (lj != j) || (lk != k))
                a[si+li][sj+lj][sk+lk] = cnt;
        return;
    }
    int32_t i_new,j_new,k_new;
    int32_t si_new,sj_new,sk_new;
    int32_t tmp_cnt = ++cnt;
    // chia hinh lap phuong thang 8 khoi
    for (int32_t li = 0; li < 2; ++li)
    for (int32_t lj = 0; lj < 2; ++lj)
    for (int32_t lk = 0; lk < 2; ++lk)
    {
        i_new = i - li * pow2(n-1);
        j_new = j - lj * pow2(n-1);
        k_new = k - lk * pow2(n-1);
        si_new = si + li * pow2(n-1);
        sj_new = sj + lj * pow2(n-1);
        sk_new = sk + lk * pow2(n-1);
        if (inside(n-1,i_new,j_new,k_new))
            Fill(n-1,i_new,j_new,k_new,si_new,sj_new,sk_new);
        else
        {
            i_new = si+pow2(n-1)-1+li;
            j_new = sj+pow2(n-1)-1+lj;
            k_new = sk+pow2(n-1)-1+lk;
            a[i_new][j_new][k_new] = tmp_cnt;
            Fill(n-1,i_new-si_new,j_new-sj_new,k_new-sk_new,si_new,sj_new,sk_new);
        }
    }
}

int32_t main()
{
    freopen("cube.inp","r",stdin);
    freopen("cube.out","w",stdout);
    cin >> n >> i >> j >> k;
    --i;--j;--k;
    memset(a,-1,sizeof(a));
    a[i][j][k] = 0;
    Fill(n,i,j,k,0,0,0);
    for (int32_t li = 0; li < pow2(n); ++li)
    {
        for (int32_t lj = 0; lj < pow2(n); ++lj)
        {
            for (int32_t lk = 0; lk < pow2(n); ++lk)
                cout << a[li][lj][lk] << " ";
            cout << endl;
        }
    }
    return 0;
}
