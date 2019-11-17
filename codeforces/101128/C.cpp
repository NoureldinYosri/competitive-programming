#ifdef ACITVE
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int n;
int t;
int a[100100];
ll sum[100100];

ll gt(int l, int m, int r)
{
    return abs((sum[r] - sum[m]) - (sum[m] - sum[l-1]));
}
ll solve(int l, int r)
{
    if (l >= r) return 0;
    if(l == r) return a[l];

    int tmpl = l, tmpr = r;
    while (r-l+1 >= 3) {
        int m1 = l + (r-l+1)/3 ;
        int m2 = m1 + (r-l+1)/3 ;
        if (gt(tmpl, m1, tmpr) >= gt(tmpl, m2, tmpr))
            l = m1 + 1;
        else r = m2 - 1;
    }

    int p = l;
    if(gt(tmpl,l,tmpr) >= gt(tmpl,r,tmpr)) p = r;
    if(p == tmpl) p++;

    return sum[tmpr]
					 - sum[tmpl-1]
						   + solve(tmpl, p-1) + solve(p, tmpr);;
}
int main(){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif

    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
            scanf("%d", &a[i]), sum[i] = sum[i-1] + a[i];
        printf("%lld\n", solve(1, n));
    }

	return 0;
}
#endif
