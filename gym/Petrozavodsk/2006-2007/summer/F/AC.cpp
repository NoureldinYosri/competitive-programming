#include <bits/stdc++.h>
#define ll long long
using namespace std;
struct Node
{
    int l, r;
    ll num, sum;
    int flag;
} T[400010];
int x[100010];

void pushdown(int rt)
{
    if (T[rt].l == T[rt].r) return;
    int ls = rt << 1, rs = rt << 1 | 1;
    if (T[rt].flag != -1)
    {
        T[ls].sum = T[rs].sum = 0;
        T[ls].num = T[rs].num = 0;
        T[ls].flag = T[rs].flag = 0;
        T[rt].flag = -1;
    }
}

void pushup(int rt)
{
    if (T[rt].l == T[rt].r) return;
    int ls = rt << 1, rs = rt << 1 | 1;
    T[rt].sum = T[ls].sum + T[rs].sum;
    T[rt].num = T[ls].num + T[rs].num;
}

void build(int rt, int l, int r)
{
    T[rt].r = r;
    T[rt].l = l;
    T[rt].sum = T[rt].num = 0;
    T[rt].flag = -1;
    if (l == r) return;
    int ls = rt << 1, rs = rt << 1 | 1;
    int mid = l + r >> 1;
    build(ls, l, mid);
    build(rs, mid+1, r);
}

void insert(int rt, int c, int n)
{
    T[rt].sum += (ll) c * n;
    T[rt].num += n;
    if (x[T[rt].l] == c && x[T[rt].r] == c) return;
    pushdown(rt);
    int ls = rt << 1, rs = rt << 1 | 1;
    if (c <= x[T[ls].r]) insert(ls, c, n);
    else insert(rs, c, n);
}

ll query(int rt, int n)
{
    if (T[rt].l == T[rt].r) return (ll) n * x[T[rt].l];
    int ls = rt << 1, rs = rt << 1 | 1;
    pushdown(rt);
    if (T[ls].num >= n) return query(ls, n);
    else return T[ls].sum + query(rs, n - T[ls].num);
}

void clear(int rt, int n)
{
    if (T[rt].l == T[rt].r)
    {
        T[rt].num -= n;
        T[rt].sum = T[rt].num * x[T[rt].l];
        return;
    }
    pushdown(rt);
    int ls = rt << 1, rs = rt << 1 | 1;
    if (T[ls].num >= n) clear(ls, n);
    else
    {
        clear(rs, n - T[ls].num);
        T[ls].num = T[ls].sum = 0;
        T[ls].flag = 0;
    }
    pushup(rt);
}

struct Query
{
    char op[10];
    int n;
    ll c;
} q[100010];

int main()
{
    int n = 0;
    int tot = 0;
    while (scanf("%s%d%lld", q[n].op, &q[n].n, &q[n].c) != EOF)
    {
        if (q[n].op[0] == 'A') x[tot ++] = q[n].c;
        n ++;
    }
    sort(x, x + tot);
    tot = unique(x, x + tot) - x;
    build(1, 0, tot - 1);
    for (int i = 0; i < n; i ++)
    {
        if (q[i].op[0] == 'A')
            insert(1, q[i].c, q[i].n);
        else
        {
            if (T[1].num < q[i].n) printf("UNHAPPY\n");
            else
            {
/*                if (query(1, q[i].n) > q[i].c) printf("UNHAPPY\n");
                else
                {
                    printf("HAPPY\n");
                    clear(1, q[i].n);
                }
                */
            	printf("%lld\n",query(1, q[i].n));
            }
        }
    }
    return 0;
}
