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

const int MAX = 200*1000 + 10;
int out_deg[MAX];
vi ord;
int n;
bool taken[MAX];

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	if(n == 1){
		puts("1");
		return 0;
	}
	loop(i,n-1) {
		int x; scanf("%d",&x);
		out_deg[x]++;
		ord.push_back(x);
	}
	set<pi> S;
	for(int u = 1;u <= n;u++)
		if(!out_deg[u])
			S.emplace(u,u);
	
	int R = ord[0];
	printf("%d\n",R);
	while(!ord.empty()) {
		int u = ord.back(); ord.pop_back();
		pi p = *S.begin(); S.erase(S.begin());
		int val = max(u,p.first);
		int v = p.second;
		printf("%d %d\n",u,v);
		out_deg[u]--;
		if(!out_deg[u])
			S.emplace(val ,u);
	}
	return 0;
}
