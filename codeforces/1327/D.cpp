#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
typedef std::vector<int> vi;
typedef std::pair<int,int> pi;
typedef std::vector<pi> vp;
typedef long long ll;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
using namespace std;
 
int P[1 << 20], n;
int Q[1 << 20];
bool vis[1 << 20];
int color[1 << 20];
vi ring[1 << 20];
int Root[1 << 20], I[1 << 20]; 

void get_Q(int k){
	for(int i = 0;i < n;i ++){
		int r = Root[i], c = I[i];
		c = (c + k)%sz(ring[r]);
		Q[i] = ring[r][c];
	}
}
 
bool done(){
	fill(vis, vis + n, 0);
	loop(i, n) if(!vis[i]){
		int j = i;
		int c = color[i];
		bool y = 1;
		while(!vis[j]){
			y &= c == color[j];
			vis[j] = 1;
			j = Q[j];
		}
		if(y) return 1;
	}
	return 0;
}

bool is_cand[1 << 20];

int solve(){
	if(done()) return 1;
	loop(i, n) ring[i].clear();
	fill(vis, vis + n, 0);
	loop(i, n+1) is_cand[i] = 0;
	loop(i, n) if(!vis[i]){
		int j = i;
		while(!vis[j]){
			vis[j] = 1;
			I[j] = sz(ring[i]);
			Root[j] = i;
			ring[i].pb(j);
			
			j = P[j];
		}
		is_cand[sz(ring[i])] = 1;
	}
	for(int d = 1; d <= n; d++)
		for(int x = 2*d; x <= n && !is_cand[d]; x += d)
			is_cand[d] = is_cand[x];
	for(int s = 1;s <= n; s++) if(is_cand[s])  {
		get_Q(s);
		if(done()) return s;
	}
	return n;
}
 
int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		loop(i, n){
			scanf("%d", P + i);
			P[i]--;
			Q[i] = P[i];
		}
		loop(i, n) scanf("%d", color + i);
		printf("%d\n", solve());
	}
	return 0;
}
