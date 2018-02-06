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
const double PI = acos(-1);
using namespace std;

const int NUMBITS = 20,MAX = 1 << NUMBITS;
int fcnt[1 << NUMBITS],n,x;
int g[1 << NUMBITS][NUMBITS + 1];

void solve(){
	memset(fcnt,0,sizeof fcnt);
	scanf("%d",&n);
	int zeros = 0;
	loop(i,n){
		scanf("%d",&x);
//		if(x) fcnt[x]++;
//		else zeros++;
		fcnt[x]++;
	}

//	ll ans = 2*zeros * (n - zeros + 0LL) + zeros * zeros;
	ll ans = 0;
	for(int i = 0;i < MAX;i++){
		g[i][0] = fcnt[i];
		for(int b = 0;b < NUMBITS;b++){
			g[i][b + 1] = g[i][b];
			if(i & (1 << b)) g[i][b + 1] += g[i^(1 << b)][b];
		}
	}

	for(int i = 0;i < MAX;i++){
		int j = (MAX-1) ^ i;
		ans += fcnt[i] *1LL* g[j][NUMBITS];
	}
	cout << ans << endl;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	int T; scanf("%d",&T);
	while(T--) solve();
	return 0;
}
