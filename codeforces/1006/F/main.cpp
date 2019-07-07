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

const int MAXN = 20;
ll G[MAXN][MAXN],target;
int n,m;
unordered_map<ll,int> mem[MAXN][MAXN];

int dx [] = {0,1,0,-1},dy [] = {1,0,-1,0};


bool inGrid(pi p) {
	return 0 <= min(p.first,p.second) && p.first < n && p.second < m;
}

bool follow(int msk,int steps,pi startPoint,bool shift,pi & endPoint,ll & x) {
	endPoint = startPoint;
	x = G[endPoint.first][endPoint.second];
	loop(i,steps) {
		int b = (msk >> i) & 1;
		b += shift*2;
		endPoint.first += dx[b];
		endPoint.second += dy[b];
		if(!inGrid(endPoint)) return 0;
		x ^= G[endPoint.first][endPoint.second];
	}
	return 1;
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	scanf("%d %d %lld",&n,&m,&target);
	loop(i,n) loop(j,m) scanf("%lld",&G[i][j]);
	int steps = n + m - 2;
	int a = min(steps,MAXN);
	int b = steps - a;
	for(int msk = 0;msk < (1 << a);msk++) {
		pi endPoint;
		ll x;
		if(!follow(msk,a,mp(0,0),0,endPoint,x)) continue;
		mem[endPoint.first][endPoint.second][x]++;
	}
	ll ans = 0;
	for(int msk = 0;msk < (1 << b);msk++) {
		pi endPoint;
		ll x;
		if(!follow(msk,b,mp(n-1,m-1),1,endPoint,x)) continue;
		x ^= G[endPoint.first][endPoint.second];
		ll other = x ^ target;
		auto & table = mem[endPoint.first][endPoint.second];
		if(table.count(other)) ans += table[other];
	}
	cout << ans << endl;
	return 0;
}
