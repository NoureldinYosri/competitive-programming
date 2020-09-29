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
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
using namespace std;

using line = pair<int, ll> ;
int P, H;
int G[500][50];
ll pref[500][50], score[500];
int ans[500];
vp E;

line get(int i, int x){
	int j = upper_bound(G[i], G[i] + H, x) - G[i];
	line L;
	L.first = H - j;
	L.second = j ? pref[i][j-1] : 0;
	return L;
}

inline void update(int s, int e, int id1, int id2){
	//cerr << id1 << " wins over " << id2 << " in " << "[" << s << ", " << e << "]" << endl;
	E.emplace_back(s, 1);
	E.emplace_back(e + 1, -1);
}

void win(line A, line B, int s, int e, int id1, int id2){
	//cerr << "working out " << s << " " << e << " for " << id1 << " " << id2 << endl;
	if(A.first == B.first){
		if(A.second < B.second) update(s, e, id1, id2);
	}
	else if(A.first < B.first){
		ll a = B.first - A.first;
		ll b = A.second - B.second;
		// x > b/a
		ll l = b/a + 1;
		l = max(l, s + 0LL);
		if(l <= e) update(l, e, id1, id2);
	}
	else {
		ll a = A.first - B.first;
		ll b = B.second - A.second;
		// x < b/a
		ll r = b/a - 1 + (b%a > 0);
		r = min(r, e + 0LL);
		if(s <= r) update(s, r, id1, id2);
	}
}

void win(int a, int b){
	static vi V;
	V.clear();
	V.pb(0);
	
	for(int i = 0, j = 0; i < H || j < H; ){
		if(i < H && j < H){
			if(G[a][i] < G[b][j]) V.pb(G[a][i++]);
			else V.pb(G[b][j++]);
		}
		else if(i < H) V.pb(G[a][i++]);
		else V.pb(G[b][j++]);
	}

	V.pb(2e9);
	V.resize(unique(all(V)) - V.begin());
	for(int i = 0; i+1 < sz(V); i++){
		line A = get(a, V[i]);
		line B = get(b, V[i]);
		win(A, B, V[i], V[i+1] - 1, a, b);
	}
}

void solve(int POI){
//	cerr << "solving for " << POI << endl;
	E.clear();
	loop(i, P) if(i != POI) {
		win(POI, i);
//		for(auto p : E) cerr << p;
//		cerr << endl;
	}
//	for(auto p : E) cerr << p;
//	cerr << endl;
	

	int ctr = 0;
	ans[POI] = P;
	sort(all(E));
	for(int i = 0; i < sz(E);){
		int j = i;
		while(j < sz(E) && E[i].first == E[j].first) 
			ctr += E[j++].second;
		ans[POI] = min(ans[POI], P - ctr);
		i = j;
	}
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	scanf("%d %d", &P, &H);
	loop(i, P) {
		loop(j, H) scanf("%d", &G[i][j]);
		sort(G[i], G[i] + H);
		loop(j, H){
			pref[i][j] = G[i][j] + (j ? pref[i][j-1] : 0);
		}
	}

	loop(i, P) solve(i);

	loop(i, P) printf("%d\n", ans[i]);
	
	return 0;
}
