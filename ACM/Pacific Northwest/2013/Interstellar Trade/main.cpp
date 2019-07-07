#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
using namespace std;

int X[5 << 10],n;
int f(int s,int m,int e) {
	return min(X[m] - X[s],X[e] - X[m]);
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	int T; scanf("%d",&T);
	while(T--) {
		scanf("%d",&n);
		loop(i,n) scanf("%d",X + i);
		sort(X,X + n);
		int ans = INT_MAX;
		for(int i = 0;i < n;i++) {
			int m = i;
			for(int j = i;j < n;j++) {
				while(m < j && f(i,m,j) <= f(i,m+1,j))
					m++;
				int a = X[i] - X[0],c = X[n-1] - X[j];
				int b = f(i,m,j);
				int d = max(a+c,max(a,c) + b);
				ans = min(ans,d);
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
