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

vector<pl> Q[2][1 << 20];

ostream& operator << (ostream & st,const pl & p){
	st << "(" << p.xx << " ," << p.yy << ")" ;
	return st;
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	int n,m; scanf("%d %d",&n,&m);
	loop(i,m){
		ll h ,l,r,res;
		scanf("%lld %lld %lld %lld",&h,&l,&r,&res);
		Q[res][h].pb(mp(l,r));
	}
	range(h,1,n) {
		loop(res,2) {
			sort(all(Q[res][h]));
			vector<pl> tmp;
			ll s = -1,e = -1;
			for(auto p : Q[res][h]) {
				if(p.xx <= e+1-res) e = max(e,p.yy);
				else{
					if(e != -1) tmp.pb(mp(s,e));
					s = p.xx;
					e = p.yy;
				}
			}
			if(s != -1) tmp.pb(mp(s,e));
			tmp.swap(Q[res][h]);
		}
		if(Q[1][h].size() > 1) {
			puts("Game cheated!");
			return 0;
		}
		if(!Q[1][h].empty()) {
			ll s = Q[1][h][0].xx,e = Q[1][h][0].yy;
			for(auto p : Q[0][h])
				if(p.xx <= s && e <= p.yy) {
					puts("Game cheated!");
					return 0;
				}
		}
	}
	vector<pl> cur[2];

	if(Q[])
	return 0;
}
