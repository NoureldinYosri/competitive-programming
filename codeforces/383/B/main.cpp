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

const int MAX = 100*1000 + 10;
map<int,set<int> > volc;
int n,m;

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d",&n,&m);
	loop(i,m) {
		int x,y; scanf("%d %d",&x,&y);
		volc[x].insert(y);
	}
	volc[n].insert(n+1);
	int lst = -1;


	vi walls;
	map<int,int> R;

	R[1] = n;

	for(auto & p : volc) {
		int x = p.xx;
		if(x != lst+1)
			R.rbegin()->yy = n;

		p.yy.insert(n+1);
		int lsty = -1;
		for(int y : p.yy){
			auto ptr = R.lower_bound(y);
			if(ptr != R.end()){
				if(ptr->xx == y) {
					int r = R[y];
					R.erase(y);
					if(y+1 <= r) R[y+1] = r;
				}
				ptr = R.lower_bound(y);
			}
			if(ptr != R.begin()){
				--ptr;
				int l = ptr->xx,r = ptr->yy;
				if(l == lsty) continue;
				lsty = l;
				if(r < y) {
					R[l] = y-1;
				}
				else {
					R[l] = y-1;
					if(y+1 <= r) R[y+1] = r;
				}
			}
		}

		if(R.empty()) {
			puts("-1");
			return 0;
		}

		lst = x;
		if(x == 1) {
//			cerr << "this is row 1" << endl;
			if(R.begin()->xx != 1) {
				puts("-1");
				return 0;
			}
			int r = R[1];
			R.clear();
			R[1] = r;
		}
//		print(p.yy,int);
//		for(auto p : R){
//			prp(p);
//		}
//		cerr << endl;
	}

	bool y = R.rbegin()->yy == n;
	if(!y) puts("-1");
	else printf("%d\n",2*n-2);
	return 0;
}
