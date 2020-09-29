#include<map>
#include<queue>
#include<time.h>
#include<limits.h>
#include<cmath>
#include<ostream>
#include<iterator>
#include<set>
#include<stack>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
#define rep_1(i,m,n) for(int i=m;i<=n;i++)
#define mem(st) memset(st,0,sizeof st)
typedef long long ll;
typedef pair<int, int> pii;
const int N = 1e5 + 5, mod = 998244353;
void solve()
{
	int n, m;
	cin >> n >> m;
	vector <int> a(n), b(m);
	for (int i = 0; i < n; i++)
		cin >> a[i];
	for (int i = 0; i < m; i++)
		cin >> b[i];
	vector <int> r(m, -1);
	//找b中每个数出现的最后一个位置
	for (int i = n - 1, j = m - 1; i >= 0; i--)
	{
		if (j >= 0 && a[i] == b[j])
		{
			r[j] = i;
			--j;
		}
	}
	//如果有没出现过的 直接是0
	if (r[0] == -1)
	{
		cout << 0 << endl;
		return;
	}
	r.push_back(n);
	//如果出现更小的
	for (int i = 0; i < r[0]; i++)
	{
		if (a[i] < b[0])
		{
			cout << 0 << endl;
			return;
		}
	}
	//b中每个数
	for (int j = 0; j < m; j++)
	{
		//这个数在a中出现的最后一个位置     一直到下个数出现的最后的位置
		for (int i = r[j] + 1; i < r[j + 1]; i++)
		{
			//如果这中间出现了比他小的，那么就一定不行  因为这个数无论跟j还是j+1，都会带偏
			if (a[i] < b[j])
			{
				cout << 0 << endl;
				return;
			}
		}
	}
	int ans = 1;
	for (int i = 0; i < m - 1; i++)
	{
		//上一个数出现的最后的位置
		int j = r[i + 1];
		//上一个数出现的最后位置 大于当前数出现的最后位置 的下标
		//且 j位置的数是大于上一个数的 那么就可以往前推，因为这个数无论放在哪边都可以
		while (j > r[i] && a[j] >= b[i + 1])
			--j;//把这样的数都找到，直接俄乘
		ans = 1ll * ans * (r[i + 1] - j) % mod;
	}
	cout << ans << endl;
}
int main()
{
	int t=1;
	while(t--)
		solve();
	return 0;
}
 	     		    				    	    	 	
