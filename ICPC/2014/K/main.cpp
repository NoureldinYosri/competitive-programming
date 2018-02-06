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

int n,K;
vp P;
pi best[2 << 20];

ostream& operator << (ostream & st,const pi & p) {
	st << "(" << p.xx << ", " << p.yy << ")";
	return st;
}

inline void insert(pi p,vp & window) {
	while(!window.empty() && p.yy >= window.back().yy) window.pop_back();
	window.pb(p);
}

bool better(pi a,pi b) {
	return a.yy < b.yy;
}

void preprocess(){
	for(auto p : P){
		if(better(best[p.xx],p))
			best[p.xx] = p;
	}
	for(int i = 1;i <= 2*n + 1;i++){
		if(better(best[i],best[i-1]))
			best[i] = best[i - 1];
	}
}

void fix(deque<pi> & used,int st,int en,int & covered) {
	static vp aux;
	int cur = st-1;
	while(!used.empty() && used.front().yy < st) used.pop_front();

	while(!used.empty() && better(used.front(),best[cur + 1])) {
		used.pop_front();
		aux.push_back(best[cur + 1]);
		cur = best[cur + 1].yy;
		if(cur >= en) {
			used.clear();
			break;
		}
	}
	reverse(all(aux));
	for(auto p : aux) used.push_front(p);
	aux.clear();
	covered = max(covered,cur);
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d",&n,&K);
	P.reserve(2*K);
	for(int i = 0;i < K;i++) {
		int a,b; scanf("%d %d",&a,&b);
		if(a <= b) {
			P.push_back(mp(a,b));
			P.push_back(mp(a+n,b+n));
		}
		else
			P.push_back(mp(a,b + n));
	}
	sort(all(P));
	preprocess();
	vp window;
	deque<pi> used;
	int ans = INT_MAX,en;
	for(int st = 1,covered = 0,j = 0;st <= n;st++) {
		covered = max(covered,st-1);
		en = st + n - 1;
		fix(used,st,en,covered);
		window.clear();
		do{
			while(covered < en && j < sz(P) && P[j].xx <= covered + 1) {
				insert(P[j],window);
				j++;
			}
			if(!window.empty()) {
				covered = max(covered,window[0].yy);
				used.pb(window[0]);
			}
		}while(covered < en && j < sz(P) && P[j].xx <= covered + 1);
//		cerr << sz(used) << " [" << st << ", " << en << "] " << " " << covered << " " << P[j].xx << endl;
//		for(auto p : used) {
//			prp(p);
//		}
//		cerr << endl;
		if(covered >= en)
			ans = min(ans,sz(used));
	}
	if(ans >= INT_MAX) puts("impossible");
	else printf("%d\n",ans);
	return 0;
}
