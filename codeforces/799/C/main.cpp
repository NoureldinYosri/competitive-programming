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
#define pl pair<ll,ll>
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

int n,c,d;
vp C,D;

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d %d",&n,&c,&d);
	loop(i,n){
		int beauty,price; char type;
		scanf("%d %d %c",&beauty,&price,&type);
		if(type == 'C') C.pb(mp(price,beauty));
		else D.pb(mp(price,beauty));
	}
	sort(all(C));
	sort(all(D));
	while(!C.empty() && C.back().xx > c) C.pop_back();
	while(!D.empty() && D.back().xx > d) D.pop_back();
	int ans = 0;
	if(!C.empty() && !D.empty()) {
		int mx = 0;
		for(auto p : C) mx = max(mx,p.yy);
		ans = mx;
		mx = 0;
		for(auto p : D) mx = max(mx,p.yy);
		ans += mx;
	}

	int mx = 0;
	for(int i = 0;i < sz(C);i++){
		auto p = upper_bound(C.begin(),C.begin() + i,mp(c - C[i].xx,INT_MAX));
		if(p != C.begin()) {
			--p;
			ans = max(ans,p->yy + C[i].yy);
		}
		C[i].yy = mx = max(mx,C[i].yy);
	}
	mx = 0;
	for(int i = 0;i < sz(D);i++){
		auto p = upper_bound(D.begin(),D.begin() + i,mp(d - D[i].xx,INT_MAX));
		if(p != D.begin()) {
			--p;
			ans = max(ans,p->yy + D[i].yy);
		}
		D[i].yy = mx = max(mx,D[i].yy);
	}
	cout << ans << endl;
	return 0;
}
