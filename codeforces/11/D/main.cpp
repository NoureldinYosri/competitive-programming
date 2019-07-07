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

const int MAXE = 20*20;
int n,m;
vi E[MAXE];
int fr[MAXE],to[MAXE];
ll dp[19][1 << 19];
int root;
inline bool checkBit(int msk,int b) {
	return (msk >> b) & 1;
}
string bin(int msk) {
	string s(n,'0');
	loop(b,n) s[b] = checkBit(msk,b) + '0';
	return s;
}

ll solve(int u,int msk){
	if(u == root && msk) return popcnt(msk) > 2;
	ll & ret = dp[u][msk];
	if(ret != -1) return ret;
//	cerr << root << ": " << u << " " << bin(msk) << endl;
	ret = 0;
	for(int e : E[u]) {
		int v = fr[e] + to[e] - u;
		if(v < root) continue;
		if(v != root && checkBit(msk,v)) continue;
		ret += solve(v,msk | (1 << u));
	}
//	if(root == 0) cerr << u << " " << bin(msk) << ": " << ret << endl;
	return ret;
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	scanf("%d %d",&n,&m);
	loop(e,m){
		int a,b; scanf("%d %d",&a,&b);
		a--,b--;
		fr[e] = a;
		to[e] = b;
		E[a].push_back(e);
		E[b].push_back(e);
	}
	ll ans = 0;
	for(root = 0;root < n;root++) {
		memset(dp,-1,sizeof dp);
		ll tmp = solve(root,0);
		assert(tmp%2 == 0);
		tmp >>= 1;
//		cerr << root << ": " << tmp << endl;
		ans += tmp;
	}
	cout << ans << endl;
	return 0;
}
