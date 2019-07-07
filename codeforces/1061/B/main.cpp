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

const int MAX = 100*1000 + 10;
int A[MAX],n;

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	int m;
	scanf("%d %d",&n,&m);
	loop(i,n) scanf("%d",A + i);
	sort(A,A + n);
	reverse(A,A + n);
	ll ans = 0;
	int h = A[0]+1;
	for(int i = 0;i < n;) {
		int j = i;
		while(j < n && A[i] == A[j]) j++;
		ll len = j - i,ch = min(A[i],h-1);
		ll tmp = len + max(h - A[i] - 1,0);
		if(ch >= len)
			h = ch - len + 1;
		else h = 1;
		ans += tmp;
		i = j;
	}
	ans += h - 1;
	ans = -ans;
	loop(i,n) ans += A[i];
	cout << ans << endl;
	return 0;
}
