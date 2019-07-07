#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
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

char P[40];
int D,len;

ll eval() {
	ll ret = 0,p = 1;
	loop(i,len){
		if(P[i] == 'S') ret += p;
		else p <<= 1;
	}
	return ret;
}

int solve(){
	int ans = 0;
	len = strlen(P);
	for(;eval() > D;ans++) {
		int lst = -1;
		for(int i = 0;i+1 < len;i++)
			if(P[i] == 'C' && P[i+1] == 'S')
				lst = i;
		if(lst == -1) return -1;
		swap(P[lst],P[lst+1]);
	}
	return ans;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	int T; scanf("%d",&T);
	for(int t = 1;t <= T;t++) {
		scanf("%d %s",&D,P);
		int res = solve();
		printf("Case #%d: ",t);
		if(res == -1) puts("IMPOSSIBLE");
		else printf("%d\n",res);
	}
	return 0;
}
