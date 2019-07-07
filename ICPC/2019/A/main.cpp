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
int n;
int H[2][MAX],P[2][MAX];
vi ord[2];


int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	scanf("%d",&n);
	map<int,vi> Q[2];
	for(int j = 0;j < 2;j++) {
		for(int i = 1;i <= n;i++) {
			scanf("%d",P[j] + i);
			Q[j][P[j][i]].push_back(i);
		}
		for(int i = 1;i <= n;i++) {
			scanf("%d",H[j] + i);
		}
	}
	set<pi> S[2];


	bool f = 1;
	loop(r,n){
		for(int j = 0;j < 2;j++) {
			if(!S[j].empty()) continue;
			const vi V = Q[j].begin()->second;
			Q[j].erase(Q[j].begin());
			for(int i : V)
				S[j].insert(mp(H[j][i],i));
		}

		int tmp = S[1].begin()->first;
		auto itr = S[0].lower_bound(mp(tmp,INT_MAX));

		if(itr == S[0].end()){
			f = 0;
			break;
		}
		int a = itr->second;
		int h = itr->first;
		S[0].erase(itr);
		ord[0].push_back(a);
//		cerr << a << endl;
//		for(auto p : S[1]) {
//			prp(p);
//		}
//		cerr << endl;
		auto ptr = S[1].lower_bound(mp(h,-1));
		if(ptr == S[1].begin()) {
			f = 0;
			break;
		}
		ptr--;
		ord[1].push_back(ptr->second);
		S[1].erase(ptr);
	}
	if(f){
		loop(j,2) {
			loop(i,n) printf("%d%c",ord[j][i]," \n"[i==n-1]);
		}
	}
	else puts("impossible");

	return 0;
}
