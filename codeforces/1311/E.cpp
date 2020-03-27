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

const int MAX = 5 << 10;
int P[MAX];
int n, d;
int depth[MAX];
int child_cnt[MAX];
vi cand[MAX];
vi leafs;

bool solve(){
	depth[1] = 0;
	for(int i = 2;i <= n; i++){
		P[i] = i-1;
		depth[i] = i-1;
	}
	for(int i = 1;i <= n;i++){
		child_cnt[i] = i < n;
	}
	for(int i = 1; i <= n; i++) if(child_cnt[i] < 2) cand[depth[i]].pb(i);
	leafs.pb(n);
	
	int s = (n*(n-1))/2;

	while(d < s){
		while(!leafs.empty()){
			int d = depth[leafs.back()];
			if(d >= 2 && !cand[d-2].empty()) break;
			leafs.pop_back();
		}
		
		if(leafs.empty()) break;
	
		int v = leafs.back();
		int h = depth[v];
		
		depth[v]--;
		s--;
		
		int p = P[v];
		child_cnt[p]--;
		if(!child_cnt[p]) leafs.pb(p);
		
		p = cand[h-2].back(); 
		
		P[v] = p;
		child_cnt[p]++;
		if(child_cnt[p] == 2)
			cand[h-2].pop_back();
	}
	return d == s;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--){
		scanf("%d %d", &n, &d);
		if(solve()){
			puts("YES");
			for(int i = 2;i <= n;i++)
				printf("%d%c", P[i], " \n"[i==n]);
		}
		else puts("NO");
	}
	return 0;
}
