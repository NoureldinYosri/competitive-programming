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

const int MAX = 1 << 20;
map<int,int> C[MAX];

int query(map<int,int> & C,int w) {
	if(C.empty()) return 0;
	auto ptr = C.upper_bound(w);
	if(ptr == C.begin()) return 0;
	ptr--;
	return ptr->yy;
}

void update(map<int,int> & C,int w,int r) {
	static vi aux;
	if(query(C,w) >= r) return;
	C[w] = r;
	auto ptr = C.upper_bound(w);
	for(;ptr != C.end() && ptr->yy <= r;ptr++)
		aux.push_back(ptr->xx);
	for(int x : aux)
		C.erase(x);
	aux.clear();
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	int n,m; scanf("%d %d",&n,&m);
	int ans = 0;
	loop(e,m) {
		int a,b,w; scanf("%d %d %d",&a,&b,&w);
		int r = query(C[a],w-1) + 1;
		ans = max(ans,r);
		update(C[b],w,r);
	}
	printf("%d\n",ans);
	return 0;
}
